# Adaptive Sensor Socket

### 1. Introduction
This project was made for the Ubiquitous Computing course at the KIT University in Karlsruhe.
In this repository you find code, business models, sketches etc. of a arduino based smart socket with replaceable sensors. You can imagine this by thinking of a nighlight with movement sensor like this: https://www.amazon.de/Bewegungsmelder-energiesparend-Steckdosenlicht-Sensorleuchte-Kinderzimmer/dp/B01LYATBR3/ref=sr_1_3?ie=UTF8&qid=1523375279&sr=8-3&keywords=sensor+steckdose.
But in this project you can easily replace the motion sensor with whatever sensor you like.

### 2. Project idea
The main problem i wanted to solve with this project was to automatically restart my internet router when it hangs up or no internet was available.
(This happened realy often to me :( )
While thinking on how to achive this i came up with a lot more usefull usecases where i would need a sensor based smart socket. But every use case needs a different sensor. So i decided to make one device where you can decide by yourself which sensor you want to use.

### 3. Requirements

The main requirements for this project where:

| Requirement    |     Description |
|:--------|:-------------------- |
|Many Sensors |The socket should work with many different sensor|
|Simple User Interface |The user interface should be simple and easy to use for everyone|
|Mobile Friendly|The interface should scale to screensize to be used on mobile phones and tablets|
|Visualize Sensor Value|The sensor value should be visualized in the UI|
|Acces Point Mode|If no wifi is available the device should work as access point|

### 4. Design Decicion
The first idea was to house all my electronics in the main socket housing. But with the size of the arduino, relay and step down it was just not possible to do this. So i decided to 3D print a case which will be mounted on top of the socket where all my electronics fit in

### 5. Hardware
This is a list of all my hardware parts i used for this project

| Amount   |      Part Type      |  Descripiton | Price |
|----------|:---------------------|:------| :------|
|1| NodeMCU v3 | The main computing part where all the logic is implemented in | 3 $
|1|230v / 5v stepdown|Get the current from the socket to power the NodeMCU| 1$
|1|Standard Socket|| 4.99 $
|1|230v relay|Relay to power the socket on and off| 1 $
|1|Sensors | Different sensors to attach to the socket|1 - 3 $
|1|3d-printed housing |PLA consumtion ca. 100g  |ca. 5 $
|**Total:**|||**15.99 $**


### 6. Schema
Shows the general setup and connection of the hardware components.  Created with [Fritzing](http://fritzing.org/home/)

![schema of project][schema]

### 7. Housing

For the housing i decied to 3D print a case where the NodeMCU and the relay with the power step down module fits in, which will be screwed on the main socket.
I also wanted to make a houseing for the different sensors but decided to make just an example for the PIR motion sensor. The rest is up to you ;)

To get an idea about the model you can see the model [here](docs/housing/housing.pdf)

And here is a timelapse of the printing:

![timelapse of printing][print]


### 8. Business Model Canvas
The business model was modulated with canvas. The result can be seen here.
If i wanted to sell this product i would chose the Direct Sales or	Low-Cost Model.

![business model canvas][bmc]

### 9. Cost Estimation
The cost estimation of around $101000 for this project was done using [COSYSMO](http://csse.usc.edu/tools/ExpertCOSYSMO.php).

### 10. Possible Improvements
* Collect historic data
* Visualize historic data with charts
* Connect to the cloud
* Optical feedback (Status LED)
* Measure current Consumption

### 11. Power Consumption

| Part   |      Consumption     |
|----------|:---------------------|
| Relay | 45mA
|Motion Sensor | 1mA
|NodeMCU| 150 mA
|**Overall**| **ca. 200mA**

### 12. Market

##### Market Research:
The smart home market is expected to be valued at USD 137.91 Billion by 2023, growing at a CAGR of 13.61% between 2017 and 2023. [source](https://www.prnewswire.com/news-releases/smart-home-market-growing-at-a-cagr-of-1361-during-2017-to-2023---reportsnreports-636315143.html)

##### Similar Products:
There are no identical products like this on the market.
Standard smart sockets are priced between 10€ to 50€.
Smart sockets with sensors are not available right now, except for motion sensor sockets. These are priced between 15€ and 60€
[Homecube Smart Socket](https://www.amazon.de/Steckdose-Homecube-intelligente-Verbrauchsanzeige-funktioniert/dp/B076Q2FDY2/ref=sr_1_6?ie=UTF8&qid=1523448473&sr=8-6&keywords=smart+socket)  38.99€ (01.04.2018)
[Belkin Motion Socket](https://www.amazon.de/Automation-Motion-Sensor-intelligente-Steckdose-Android-Ger%C3%A4te/dp/B008TPW2EU/ref=sr_1_6?s=diy&ie=UTF8&qid=1523448552&sr=1-6&keywords=sensor+steckdose) 46.95€ (01.04.2018)

[schema]: fritzing/fritzing_bb.png "Schema from SmartKanne"
[bmc]: docs/AdaptiveSensorSocket-Canvas-Canvanizer.pdf "Business Model Canvas"
[print]: docs/printing.mp4  "3d printing of housing timelapse"
