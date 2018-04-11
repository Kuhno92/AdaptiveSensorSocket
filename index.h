const char SITE_index[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" /> 
<link rel="stylesheet" href="http://code.jquery.com/mobile/1.4.5/jquery.mobile-1.4.5.min.css" />
<script src="http://code.jquery.com/jquery-1.11.1.min.js"></script>
<script src="http://code.jquery.com/mobile/1.4.5/jquery.mobile-1.4.5.min.js"></script>
<script type="text/javascript">
    if (typeof jQuery == 'undefined') {
        document.write(unescape('%3Clink rel="stylesheet" type="text/css" href="\\jquery.mobile-1.4.5.min.css" /%3E'));
        document.write(unescape('%3Cscript type="text/javascript" src="\\jquery-1.11.1.min.js" %3E%3C/script%3E'));
        document.write(unescape('%3Cscript type="text/javascript" src="\\jquery.mobile-1.4.5.min.js" %3E%3C/script%3E'));
    }
</script>

<body>
  <div data-role="page" data-theme="b">
    <div data-role="header">
      <h1>Adaptive Sensor Socket</h1>
    </div>

    <div id="main" data-role="main" class="ui-content">

      <h1>Socket:</h1>
      
      <div data-role="content">
        <div class="ui-grid-a">
            <div class="ui-block-a socket"><a href="#" data-role="button" data-icon="check">ON</a> </div>
            <div class="ui-block-b socket"> <a href="#" data-role="button" data-icon="delete">OFF</a> </div>
        </div>
      </div>

      <h1>Sensors:</h1>
      <div data-role="collapsible" id="SensorCollapsible" style="margin-left: 20px; margin-right: 20px;">
        <h4>Sensor Type</h4>
        <input class="btnmode" value="Motion Sensor" type="button" 
          style="background-image: url(https://d30y9cdsu7xlg0.cloudfront.net/png/1542572-200.png);">
        <input class="btnmode" value="Ultrasonic Sensor" type="button"
          style="background-image: url(https://senix.com/wp-content/uploads/2015/05/icon-3-distance-ranging.png);">
        <input class="btnmode" value="Microphone" type="button"
          style="background-image: url(https://cdn4.iconfinder.com/data/icons/eldorado-devices/40/microphone-512.png); ">
        <input class="btnmode" value="Temperature Sensor" type="button"
          style="background-image: url(https://static.srvrschck.com/images/temperature-icon.png);">
        <input class="btnmode" value="Humidity Sensor" type="button" 
          style="background-image: url(https://image.winudf.com/v2/image/Y29tLmlkcmlzeWlsZGl6LnJvb210ZW1wYW5kaHVtX2ljb25fMF9hMjI0YTcwOA/icon.png?w=170&fakeurl=1&type=.png); ">
        <input class="btnmode" value="Network Sensor" type="button" 
          style="background-image: url(http://icons.iconarchive.com/icons/custom-icon-design/pretty-office-12/512/wifi-icon.png); ">
          <input class="btnmode" value="No Sensor" type="button" 
          style="background-image: url(https://cdn3.iconfinder.com/data/icons/pix-glyph-set/50/520753-not_allowed-512.png); ">
      </div>

      <div id="Motion Sensor" class="sensor" style="display: none">
        <div class="ui-field-contain" style="padding-top: 1.33em">
          <label for="flip-2" style="width: auto"><h4 style="-webkit-margin-before: 0px;">Socket Activation Functions:</h4></label>
          <select name="flip-2" class="sensorActiveButton" data-role="flipswitch" data-mini="true" data-theme="b"><option value="sensorInactive">OFF</option><option value="sensorActive">ON</option></select>
        </div>
        <div id="UTimeoutDelaySlider" class="ui-slider-slider" style="text-align: center; color:white; text-shadow: black 0.1em 0.1em 0.2em;""> 
          <label style="font-size: 130%;">Delay(min) :</label>
          <input class="SensorConfigSlider1" id="Timeout" type="range" min="0" max="1440" value="1" data-theme="a" data-track-theme="b" />
        </div>
        <br>
        <h4>Current Sensor Value:</h4>
        <textarea name="textarea" disabled id="textarea-a" cols="1" rows="1" style="color: #FFFFFF; opacity: 0.8; padding-left: -100px;">
          Reading Sensor Value ...
        </textarea>
      </div>

      <div id="Ultrasonic Sensor" class="sensor" style="display: none">
        <div class="ui-field-contain" style="padding-top: 1.33em">
          <label for="flip-2" style="width: auto"><h4 style="-webkit-margin-before: 0px;">Socket Activation Functions:</h4></label>
          <select name="flip-2" class="sensorActiveButton" data-role="flipswitch" data-mini="true" data-theme="b"><option value="sensorInactive">OFF</option><option value="sensorActive">ON</option></select>
        </div>
        <div id="UltrasonicDistanceSlider" class="ui-slider-slider" style="text-align: center; color:white; text-shadow: black 0.1em 0.1em 0.2em;""> 
          <label style="font-size: 130%;">Distance(cm) :</label>
          <input class="SensorConfigSlider1" id="distance" type="range" min="2" max="700" value="10" data-theme="a" data-track-theme="b" />
        </div>
        <br>
        <h4>Current Sensor Value:</h4>
        <textarea name="textarea" disabled id="textarea-a" cols="1" rows="1" style="color: #FFFFFF; opacity: 0.8; padding-left: -100px;">
          Reading Sensor Value ...
        </textarea>
      </div>

      <div id="Microphone" class="sensor" style="display: none">
        <div class="ui-field-contain" style="padding-top: 1.33em">
          <label for="flip-2" style="width: auto"><h4 style="-webkit-margin-before: 0px;">Socket Activation Functions:</h4></label>
          <select name="flip-2" class="sensorActiveButton" data-role="flipswitch" data-mini="true" data-theme="b"><option value="sensorInactive">OFF</option><option value="sensorActive">ON</option></select>
        </div>
        <div id="SoundDBSlider" class="ui-slider-slider" style="text-align: center; color:white; text-shadow: black 0.1em 0.1em 0.2em;""> 
          <label style="font-size: 130%;">Delay(min) :</label>
          <input class="SensorConfigSlider1" id="Loudness" type="range" min="0" max="200" value="50" data-theme="a" data-track-theme="b" />
        </div>
        <br>
        <h4>Current Sensor Value:</h4>
        <textarea name="textarea" disabled id="textarea-a" cols="1" rows="1" style="color: #FFFFFF; opacity: 0.8; padding-left: -100px;">
          Reading Sensor Value ...
        </textarea>
      </div>

      <div id="Temperature Sensor" class="sensor" style="display: none">
        <div class="ui-field-contain" style="padding-top: 1.33em">
          <label for="flip-2" style="width: auto"><h4 style="-webkit-margin-before: 0px;">Socket Activation Functions:</h4></label>
          <select name="flip-2" class="sensorActiveButton" data-role="flipswitch" data-mini="true" data-theme="b"><option value="sensorInactive">OFF</option><option value="sensorActive">ON</option></select>
        </div>
        <div id="TemperaturSlider" class="ui-slider-slider" style="text-align: center; color:white; text-shadow: black 0.1em 0.1em 0.2em;""> 
          <label style="font-size: 130%;">Temperature(°C) :</label>
          <input class="SensorConfigSlider1" id="Temperature" type="range" min="-30" max="200" value="22" data-theme="a" data-track-theme="b" />
        </div>
        <br>
        <h4>Current Sensor Value:</h4>
        <textarea name="textarea" disabled id="textarea-a" cols="1" rows="1" style="color: #FFFFFF; opacity: 0.8; padding-left: -100px;">
          Reading Sensor Value ...
        </textarea>
      </div>

      <div id="Humidity Sensor" class="sensor" style="display: none">
        <div class="ui-field-contain" style="padding-top: 1.33em">
          <label for="flip-2" style="width: auto"><h4 style="-webkit-margin-before: 0px;">Socket Activation Functions:</h4></label>
          <select name="flip-2" class="sensorActiveButton" data-role="flipswitch" data-mini="true" data-theme="b"><option value="sensorInactive">OFF</option><option value="sensorActive">ON</option></select>
        </div>
        <div id="HumiditySlider" class="ui-slider-slider" style="text-align: center; color:white; text-shadow: black 0.1em 0.1em 0.2em;""> 
          <label style="font-size: 130%;">Humidity(%) :</label>
          <input class="SensorConfigSlider1" id="humidity" type="range" min="0" max="100" value="60" data-theme="a" data-track-theme="b" />
        </div>
        <br>
        <h4>Current Sensor Value:</h4>
        <textarea name="textarea" disabled id="textarea-a" cols="1" rows="1" style="color: #FFFFFF; opacity: 0.8; padding-left: -100px;">
          Reading Sensor Value ...
        </textarea>
      </div>
      <div id="Network Sensor" class="sensor" style="display: none;"">
        <div class="ui-field-contain" style="padding-top: 1.33em">
          <label for="flip-2" style="width: auto"><h4 style="-webkit-margin-before: 0px;">Socket Activation Functions:</h4></label>
          <select name="flip-2" class="sensorActiveButton" data-role="flipswitch" data-mini="true" data-theme="b"><option value="sensorInactive">OFF</option><option value="sensorActive">ON</option></select>
        </div>
        <br>
        <h4>Status:</h4>
        <textarea name="textarea" disabled id="textarea-a" cols="1" rows="1" style="color: #FFFFFF; opacity: 0.8; padding-left: -100px;">
          Reading Network Status ...
        </textarea>
      </div>
      <div id="No Sensor" class="sensor" style="display: none;">
       <img src="https://cdn3.iconfinder.com/data/icons/pix-glyph-set/50/520753-not_allowed-512.png" alt="image" style="display: block; margin-left: auto; margin-right: auto; width: 20vh;"/>
      </div>

      <br>
      <h1>Information</h1>
      <div data-role="collapsible" style="margin-left: 20px; margin-right: 20px"><h4>Device Info</h4>
        <ul id="info">
          <li><b>BootUp Time: </b></li>
          <li><b>Ip Adress: </b></li>
        </ul>
      </div>

      </div>
          <div data-role="footer" data-position="fixed">
          <h3 id="footer">(C) MIT License Nico Kuhn 2018</h3>
      </div>  

  </div>
</body>

  <style>
      /*First rule hides the text box, the second one makes slider full width*/
      div.ui-slider-slider input.ui-input-text {
        display: none;
      }
      div.ui-slider-slider div.ui-slider-track {
        #margin: 0 15px 0 15px !important;
      }
      input[type=range]::-webkit-slider-thumb {
        -webkit-appearance: none;
        border: none;
        height: 16px;
        width: 16px;
        border-radius: 50%;
        background: goldenrod;
        margin-top: -4px;
      }
      .ui-collapsible-heading .ui-btn  {
          text-align: center;
      }
      span > img {
          color: white;
      }
      span > input {
          background: none;
          color: white;
          padding: 0;
          border: 0;
      }

      input.btnmode {
        opacity: 1; 
        filter: brightness(0) invert(1);
        background-repeat: no-repeat; 
        background-position: right; 
        background-size: 40px 40px;
      }
      .sensor {
        margin-left: 20px;
        margin-right: 20px;
      }
      
    </style>

  <script type="text/javascript">
    $( ".socket" ).bind( "click", function(e) {
      var command = e.target.innerHTML;
      console.log("Command: " + command);
      //Disable all Sensor Functions
      $('.sensorActiveButton').each(function(i, btn) {
        btn.value = "sensorInactive";
      });
      $( ".sensorActiveButton" ).flipswitch( "refresh" );
      connection.send(command);
    });

    $( ".btnmode" ).bind( "click", function(e) {
      var type = e.target.value;
      console.log("Sensortype: " + type);
      //Update Sensor Specific Menu
      var divsToHide = document.getElementsByClassName("sensor"); //divsToHide is an array
      for(var i = 0; i < divsToHide.length; i++){
          divsToHide[i].style.display = "none"; // depending on what you're doing
      }
      document.getElementById(type).style.display = "block";
      $('#SensorCollapsible').collapsible( "collapse" );

      //Update Collapsable Header
      document.getElementById("SensorCollapsible").firstChild.firstChild.innerHTML = type + '<img src=' + e.target.style.backgroundImage.slice(4, -1) + 'alt="US Flag" style="postion: absolute; float:right; filter: brightness(0) invert(1); width:40px; height:40px; margin-top: -10px; margin-bottom: -15px" />'
      //Disable all Sensor Functions
      $('.sensorActiveButton').each(function(i, btn) {
        btn.value = "sensorInactive";
      });
      $( ".sensorActiveButton" ).flipswitch( "refresh" );

      connection.send(document.getElementsByClassName("sensorActiveButton")[0].value)
      connection.send(type);
    });

    $( ".sensorActiveButton" ).change(function(e){
      connection.send(e.target.value)
    });

    //Sensor COnfiguration Slider
    $( ".ui-slider-slider" ).on( "slidestop", function( event, ui ) {
      connection.send("SensorConfig1:"+ event.target.value);
    } );

    //Websocket
    var connection = new WebSocket('ws://' + location.host + ':81/', ['arduino']);
    connection.onopen = function () {
      connection.send('Connect ' + new Date());
    };
    connection.onerror = function (error) {
      console.log('WebSocket Error ', error);
    };
    connection.onmessage = function (e) {
      console.log('Server: ', e.data);
      parseWsData(e.data)
    };
    connection.onclose = function () {
      console.log('WebSocket connection closed');
    };

    function parseWsData(data) {
      var obj = JSON.parse(data);
      //update device info
      var items = document.getElementById("info").childNodes;
      obj.sensor.sensortype != 0 ? document.getElementsByClassName("sensor")[obj.sensor.sensortype-1].style.display = "block" : null;
      items[1].innerHTML = "<b>BootUp Time: "+"</b>"+obj.uptime; 
      items[3].innerHTML = "<b>IP Adress: "+"</b>"+obj.ip;
      //update Sensor Function Activation Buttons
      $('.sensorActiveButton').each(function(i, btn) {
        btn.value = obj.sensor.sensorActive;
      });
      $( ".sensorActiveButton" ).flipswitch( "refresh" );
      //update Sensor Menu
      obj.sensor.sensortype != 0 ? document.getElementById("SensorCollapsible").firstChild.firstChild.innerHTML = $(".btnmode")[obj.sensor.sensortype-1].value + '<img src=' + $(".btnmode")[obj.sensor.sensortype-1].style.backgroundImage.slice(4, -1) + 'alt="US Flag" style="postion: absolute; float:right; filter: brightness(0) invert(1); width:40px; height:40px; margin-top: -10px; margin-bottom: -15px" />' : null
      //update Current Sensor Value
      obj.sensor.sensortype != 0 && obj.sensor.sensorvalue != undefined ? document.getElementsByClassName("sensor")[obj.sensor.sensortype-1].querySelector('#textarea-a').innerHTML = obj.sensor.sensorvalue + " " + obj.sensor.unit : null
      //update Current Sensor Config1 Slider
      obj.sensor.SensorConfig1 != -1 && obj.sensor.SensorConfig1 != undefined ? document.getElementsByClassName("sensor")[obj.sensor.sensortype-1].getElementsByClassName("SensorConfigSlider1")[0].value = obj.sensor.SensorConfig1 : null
      $( ".SensorConfigSlider1" ).slider( "refresh" );
    }
  </script>
)=====";
