//************************************* INCLUDES *************************************************
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include <time.h>
#include "Ticker.h"
#include <WebSocketsServer.h>
#include "index.h"
//************************************* VARIABLE DECLARATION **************************************
const char* htmlfile = "/index.html";

int relayPin = D5; // the input to the relay pin
int sensor = D7;
int sensor2 = D6;

// WiFi parameters and variables
const char *ssid = "Smart_Socket_Access_Point"; // The name of the Wi-Fi network that will be created
const char *password = "123456789";   // The password required to connect to it, leave blank for
const char* mdnsName = "smartsocket";
// Create an instance of the server
ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);
ESP8266WiFiMulti wifiMulti;       // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

// Variables used to send as JSON via Websocket
String sensorActive = "sensorInactive"; //options: sensorActive; sensorInactive
int sensorType = 0; // 0 := No Sensor, 1 := Motion; 2 := Ultrasonic, 3 := Microphone, 4 := Temperature, 5 := Humidity, 6 := Network,
int currentSensorConfig1 = -1;
String uptime;
String ipadress ;

//************************************* SETUP ***************************************************
void setup() {
  pinMode(relayPin, OUTPUT); // initialize pin as OUTPUT
  pinMode(sensor2, OUTPUT); // initialize pin as OUTPUT
  pinMode(sensor, INPUT); // initialize pin as INPUT
  digitalWrite(relayPin, LOW); // init relay to off

  ESP.eraseConfig();
  
  // Start Serial
  Serial.begin(9600);
  
  //Initialize File System
  SPIFFS.begin();
  Serial.println("File System Initialized");
  Dir dir = SPIFFS.openDir("/");
    while (dir.next()) {
      String fileName = dir.fileName();
      size_t fileSize = dir.fileSize();
      Serial.printf("FS File: %s, size: %s\n", fileName.c_str(), String(fileSize).c_str());
      Serial.println();
    }

  startWiFi();
  startWebSocket();            // Start a WebSocket server
  if(WiFi.softAPgetStationNum() != 0){ startMDNS(); }  // Start the mDNS responder if AP mode
  startServer();               // Start a HTTP server with a file read handler and an upload handler
  getTime();
}
//**************************************INITIALIZATION FUNCTIONS (SETUP)************************
//===============================================================
// Wifi Initialization
// - Connects to defined AP´s or creates on AP if no AP available
//===============================================================
void startWiFi() { // Start a Wi-Fi access point, and try to connect to some given access points. Then wait for either an AP or STA connection
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ssid, password);  
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started\r\n");

  wifiMulti.addAP("DontTouchThis", "**PASSWORD**");   // add Wi-Fi networks you want to connect to
  wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2");
  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");

  Serial.println("Connecting");
  while (wifiMulti.run() != WL_CONNECTED && WiFi.softAPgetStationNum() < 1) {  // Wait for the Wi-Fi to connect
    delay(250);
    Serial.print('.');
  }
  Serial.println("\r\n");
  if(WiFi.softAPgetStationNum() == 0) {      // If the ESP is connected to an AP
    Serial.print("Connected to ");
    Serial.println(WiFi.SSID());             // Tell us what network we're connected to
    Serial.print("IP address:\t");
    Serial.print(WiFi.localIP());            // Send the IP address of the ESP8266 to the computer
    WiFi.mode(WIFI_STA);
  } else {
    // If a station is connected to the ESP SoftAP
    Serial.println("Station connected to ESP8266 AP");
    Serial.println(WiFi.softAPIP());
    WiFi.disconnect(); 
  }
  Serial.println("\r\n");
  (WiFi.softAPgetStationNum() == 0) ? ipadress = WiFi.localIP().toString() : ipadress = WiFi.softAPIP().toString();
}
//===============================================================
// Initializes MDNS service
//===============================================================
void startMDNS() { // Start the mDNS responder
  MDNS.begin(mdnsName);  // start the multicast domain name server
  Serial.print("mDNS responder started: http://");
  Serial.print(mdnsName);
  Serial.println(".local");
}
//===============================================================
// Server Initialization to handle Client Requests
// - serves main page (index.html) from index.h file (include) 
// - serves required javascripts and stylesheets from SPIFFS
//===============================================================
void startServer() { // Start a HTTP server with a file read handler and an upload handler
  server.on ( "/", []() { server.send ( 200, "text/html", SITE_index );  } );                                          // and check if the file exists
  server.onNotFound(handleWebRequests); //Set setver all paths are not found so we can handle as per URI
  server.begin(); 
  // start the HTTP server
  Serial.println("HTTP server started.");
}
//===============================================================
// Initializes Websocket Server
//===============================================================
void startWebSocket() { // Start a WebSocket server
  webSocket.begin();                          // start the websocket server
  webSocket.onEvent(webSocketEvent);          // if there's an incomming websocket message, go to function 'webSocketEvent'
  Serial.println("WebSocket server started.");
}
//************************************* LOOP ***************************************************
void loop() {
  server.handleClient();          //Handle client requests
  webSocket.loop();               // constantly check for websocket events
}

//************************************* Web Events ***************************************************
//===============================================================
// Handles Requests from the client except index.html
// - Normal usage is to serve .js and .css from SPIFFS
//===============================================================
void handleWebRequests(){
  Serial.println(server.uri());
  if(loadFromSpiffs(server.uri())) return;
  String message = "File Not Detected\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " NAME:"+server.argName(i) + "\n VALUE:" + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  Serial.println(message);
}
//===============================================================
// Handles Websocket requests
//===============================================================
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t msglength) { // When a WebSocket message is received
  if(msglength == 0) {
    //Arduino Crashes if lenght == 0
    return;
  }
  switch (type) {
    case WStype_DISCONNECTED:             // if the websocket is disconnected
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED: {              // if a new websocket connection is established
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        webSocket.sendTXT(num, "{\"uptime\": \"" + uptime + "\", \"ip\": \"" + ipadress + " \", " + "\"sensor\": {\"sensortype\": " + sensorType + ", \"sensorActive\": \""+sensorActive+"\",\"SensorConfig1\": \""+currentSensorConfig1+"\" }}"); 
      }
      break;
    case WStype_TEXT:                     // if new text data is received
      Serial.printf("[%u] WebSocketMessaget: %s\n", num, payload);
      parseWsCommands(payload);
      break;
  }
}
//************************************* Sensor Routines ***************************************************
//===============================================================
// Motion Sensor Routine
//===============================================================
Ticker motionTicker;
String motion = "No motion";
int socketDelay = 1;
void motionSensorRoutine() {
  long state = digitalRead(sensor);
  if(state == LOW) {
    socketOn();
    motion = "Motion detected !!!";
    motionTicker.attach(socketDelay, motionSensorRoutine);
  }
  else {
    socketOff();
    motion = "No motion";
    motionTicker.attach(1, motionSensorRoutine);
  }
  webSocket.sendTXT(0, "{\"uptime\": \"" + uptime + "\", \"ip\": \"" + ipadress + " \", " + "\"sensor\": {\"sensortype\": " + sensorType + ", \"sensorvalue\": \""+ motion + "\", \"unit\": \" \", \"sensorActive\": \""+sensorActive+"\"}}");
}
//===============================================================
// Ultrasonic Sensor Routine
//===============================================================
// defines variables
int triggerDistance = 10; //cm
long duration;
int distance;
Ticker ultrasonicTicker;
void ultrasonicSensorRoutine() { 
  // Clears the trigPin
  digitalWrite(sensor2, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(sensor2, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensor2, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(sensor, HIGH);
  
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  //Serial.print("Distance: ");
  //Serial.println(distance);
  webSocket.sendTXT(0, "{\"uptime\": \"" + uptime + "\", \"ip\": \"" + ipadress + " \", " + "\"sensor\": {\"sensortype\": " + sensorType + ", \"sensorvalue\": "+ distance + ", \"unit\": \"cm\", \"sensorActive\": \""+sensorActive+"\"}}");
  if(distance <= triggerDistance) {
    socketOn();
  } else {
    socketOff();
  }
}
//************************************* Sensor Routing ***************************************************
//===============================================================
// Parse Websocket commands
//===============================================================
String getValue(String data, char separator, int index);
void parseWsCommands(uint8_t *payload){
  String command = String((char *)payload);
  if( command == "ON" ) {socketOn(); }
  if( command == "OFF" ) {socketOff(); }
  if( command == "sensorActive" ) {sensorActive = "sensorActive"; sensorActionRouter(); }
  if( command == "sensorInactive" ) {sensorActive = "sensorInactive"; stopTicker(); }
  if( command == "No Sensor" ) {currentSensorConfig1 = -1; sensorType =  0; } 
  if( command == "Motion Sensor" ) {currentSensorConfig1 = -1; sensorType = 1; }
  if( command == "Ultrasonic Sensor" ) {sensorType = 2; sensorConfigurationRouter(10);}
  if( command == "Microphone" ) {currentSensorConfig1 = -1; sensorType = 3; }
  if( command == "Temperature Sensor" ) {currentSensorConfig1 = -1; sensorType = 4; }
  if( command == "Humidity Sensor" ) {currentSensorConfig1 = -1; sensorType = 5; }
  if( command == "Network Sensor" ) {currentSensorConfig1 = -1; sensorType = 6; }
  if(getValue(command, ':', 0) == "SensorConfig1" ) {sensorConfigurationRouter(getValue(command, ':', 1).toInt()); }
  if(sensorActive == "sensorActive"){sensorActionRouter();}
}
//===============================================================
// Ataches a ticker to the specified sensor
//===============================================================
void sensorActionRouter(){
  switch (sensorType) {
    case 0:
      stopTicker();
      break;
    case 1:
      stopTicker(); motionTicker.attach(1, motionSensorRoutine);
      break;
    case 2:
      stopTicker(); ultrasonicTicker.attach(0.5, ultrasonicSensorRoutine);
      break;
    case 3:
      stopTicker();
      break;
    case 4:
      stopTicker();
      break;
    case 5:
      stopTicker();
      break;
    case 6:
      stopTicker();
      break;
    default:
      stopTicker();
      break;
  }
}
//===============================================================
// Sets sensor service routine variables for the specific sensor
//===============================================================
void sensorConfigurationRouter(int config1){
  currentSensorConfig1 = config1;
  switch (sensorType) {
    case 0:
      break;
    case 1:
      socketDelay = config1;
      break;
    case 2:
      triggerDistance = config1;
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      break;
    default:
      break;
  }
}
//===============================================================
// Stops the execution of the sensor service routines
//===============================================================
void stopTicker() {
  ultrasonicTicker.detach();
  motionTicker.detach();
}
//************************************* Socket Functions ***************************************************
//===============================================================
// Turns Socket ON
//===============================================================
void socketOn() {
  digitalWrite(relayPin, HIGH); // turn relay off
  //Serial.println("Socket ON");
}
//===============================================================
// Turns Socket OFF
//===============================================================
void socketOff() {
  digitalWrite(relayPin, LOW); // turn relay on
  //Serial.println("Socket OFF");
}
//**********************************HELPER FUNCTIONS ******************************
//===============================================================
// Gets current Time from the Internet 
//===============================================================
void getTime(){
  configTime(2 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  int count = 0;
  while (time(nullptr) < 954367200 && count < 5) { // 954367200 = year 2000 in unix time
    Serial.print(":");
    delay(1000);
    count++;
  }
  time_t now = time(nullptr);
  uptime = ctime(&now);
  uptime .remove(uptime.length()-1);
  Serial.println("Start time: " + uptime);
}
//===============================================================
// Split data by seperator and return the indexed data value
//===============================================================
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
//===============================================================
// Reads requested file from SPIFFS and streams it to the client
//===============================================================
bool loadFromSpiffs(String path){
  String dataType = "text/plain";
  if(path.endsWith("/")) path += "index.htm";

  if(path.endsWith(".src")) path = path.substring(0, path.lastIndexOf("."));
  else if(path.endsWith(".html")) dataType = "text/html";
  else if(path.endsWith(".htm")) dataType = "text/html";
  else if(path.endsWith(".css")) dataType = "text/css";
  else if(path.endsWith(".js")) dataType = "application/javascript";
  else if(path.endsWith(".png")) dataType = "image/png";
  else if(path.endsWith(".gif")) dataType = "image/gif";
  else if(path.endsWith(".jpg")) dataType = "image/jpeg";
  else if(path.endsWith(".ico")) dataType = "image/x-icon";
  else if(path.endsWith(".xml")) dataType = "text/xml";
  else if(path.endsWith(".pdf")) dataType = "application/pdf";
  else if(path.endsWith(".zip")) dataType = "application/zip";
  File dataFile = SPIFFS.open(path.c_str(), "r");
  if (server.hasArg("download")) dataType = "application/octet-stream";
  if (server.streamFile(dataFile, dataType) != dataFile.size()) {
  }

  dataFile.close();
  return true;
}
