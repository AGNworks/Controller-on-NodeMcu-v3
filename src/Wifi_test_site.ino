#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESPDMX.h>

DMXESPSerial dmx;

/*
const char index_html[] PROGMEM = {};
const char style_css[] PROGMEM = {};
const char control_html[] PROGMEM = {};
*/
const char index_html[] PROGMEM = {"<!DOCTYPE html>\n    <html>\n        <head>\n            <link rel=\"stylesheet\" href=\"styles.css\">\n            <title>Index</title>\n        </head>\n        <body> \n            <h1>DMX-512 Controller</h1>\n            <button onclick=\"location.href='control.html'\"><strong>Control page</strong></button>\n            <p>With these buttons you can switch on/off all the red/green/blue/white channels</p>\n\n            <select id=\"LED type\" name=\"LED\">\n                <option>RGB</option>\n                <option>RGBW</option>\n            </select>\n\n            <div class=\"row\">\n                <div class=\"column4\">\n                    <button class=\"button button1\" onclick=\"location.href='allRED'\">RED</button>\n                </div>\n                <div class=\"column4\">\n                    <button class=\"button button2\" onclick=\"location.href='allGREEN'\">GREEN</button>\n                </div>\n                <div class=\"column4\">\n                    <button class=\"button button3\" onclick=\"location.href='allBLUE'\">BLUE</button>\n                </div>\n                <div class=\"column4\">\n                    <button class=\"button button4\" onclick=\"location.href='allWHITE'\">WHITE</button>\n                </div>\n            </div>\n            <div class=\"row\" >\n                <div class=\"column2\">\n                    <button onclick=\"location.href='allON'\">ALL ON</button>\n                </div>\n                <div class=\"column2\">\n                    <button onclick=\"location.href='allOFF'\">ALL OFF</button>\n                </div>\n            </div>\n\n        </body>\n    </html>"};
const char style_css[] PROGMEM = {"body {\n    margin-left: 20px;\n    background-color: rgb(180, 200, 202);\n  }\n\n  h1 {\n    text-align: center;\n    color: rgb(0, 0, 109);\n  }\n\n  p {\n    color: rgb(2, 111, 82);\n  }\n\n  a {\n    color: rgb(33, 86, 121);\n  }\n\n  select{\n    margin-bottom: 20px;\n  }\n\n  button{\n    padding: 20px;\n    margin-bottom: 20px;\n  }\n  .button1 {\n    background-color: rgb(250, 4, 4); \n    color: black; \n  }\n\n  .button2 {\n    background-color: rgb(62, 255, 4); \n    color: black; \n  }\n\n  .button3 {\n    background-color: rgb(4, 0, 255); \n    color: white;\n  }\n\n  .button4 {\n    background-color: rgb(185, 243, 253); \n    color: black; \n  }\n\n  .column4 {\n    float: left;\n    width: 25%;\n  }\n\n  .column2 {\n    text-align: center;\n    float: left;\n    width: 50%;\n  }\n\n  /* Clear floats after the columns */\n  .row:after {\n    content: \"\";\n    display: table;\n    clear: both;\n  }\n\n  .slidecontainer {\n    width: 100%; /* Width of the outside container */\n  }\n  \n  /* The slider itself */\n  .slider {\n    -webkit-appearance: none;  /* Override default CSS styles */\n    appearance: none;\n    width: 100%; /* Full-width */\n    height: 25px; /* Specified height */\n    background: #d3d3d3; /* Grey background */\n    outline: none; /* Remove outline */\n    opacity: 0.7; /* Set transparency (for mouse-over effects on hover) */\n    -webkit-transition: .2s; /* 0.2 seconds transition on hover */\n    transition: opacity .2s;\n  }\n  \n  /* Mouse-over effects */\n  .slider:hover {\n    opacity: 1; /* Fully shown on mouse-over */\n  }\n  \n  /* The slider handle (use -webkit- (Chrome, Opera, Safari, Edge) and -moz- (Firefox) to override default look) */\n  .slider::-webkit-slider-thumb {\n    -webkit-appearance: none; /* Override default look */\n    appearance: none;\n    width: 25px; /* Set a specific slider handle width */\n    height: 25px; /* Slider handle height */\n    background: #04AA6D; /* Green background */\n    cursor: pointer; /* Cursor on hover */\n  }\n  \n  .slider::-moz-range-thumb {\n    width: 25px; /* Set a specific slider handle width */\n    height: 25px; /* Slider handle height */\n    background: #04AA6D; /* Green background */\n    cursor: pointer; /* Cursor on hover */\n  }"};

#ifndef APSSID
#define APSSID "DMX512"
#define APPSK  "12344321"
#endif


const char *ssid = APSSID;
const char *password = APPSK;

byte ch_numb = 1;

ESP8266WebServer server(80);

// Go to http://192.168.4.1 in a web browser



//----------------------------------------------------------------------------handling
void handleRoot() {
  server.send_P(200, "text/html", index_html);
  Serial.println("index");
}

void handleCss() {
  server.send_P(200, "text/css", style_css);
}

void handleControl() {
  server.send_P(200, "text/html", control_html);
  Serial.println("control");
}

void handleIndex() {
  server.send_P(200, "text/html", index_html);
  Serial.println("index");
}

void handleallON() {
  server.send_P(200, "text/html", index_html);
  Serial.println("allon");
  change_all(255);                   
}

void handleallOFF() {
  server.send_P(200, "text/html", index_html);
  Serial.println("allOFF");
  change_all(0);
}

void handleRED() {
  server.send_P(200, "text/html", index_html);
  Serial.println("all_red");
  change_some(1,255);
}

void handleGREEN() {
  server.send_P(200, "text/html", index_html);
  Serial.println("all_red");
  change_some(2,255);
}


void handleBLUE() {
  server.send_P(200, "text/html", index_html);
  Serial.println("all_red");
  change_some(3,255);
}


void handleWHITE() {
  server.send_P(200, "text/html", index_html);
  Serial.println("all_red");
  change_some(4,255);
}


//----------------------------------------------------------------------------SETUP
void setup() {
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  
  delay(1000);
  dmx.init(512);   //we will use all the 512 DMX channels
  delay(100);

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  server.on("/", handleRoot);
  server.on("/styles.css", handleCss);
  server.on("/control.html", handleControl);
  server.on("/index.html", handleRoot);
  server.on("/allON", handleallON);
  server.on("/allOFF", handleallOFF);
  server.on("/allRED", handleRED);
  server.on("/allGREEN", handleGREEN);
  server.on("/allBLUE", handleBLUE);
  server.on("/allWHITE", handleWHITE);

  server.begin();
  Serial.println("HTTP server started");
}

//----------------------------------------------------------------------------LOOP
void loop() {
  server.handleClient();
}

//----------------------------------------------------------------------------change_all
//Changing the value of all channels with the given byte
void change_all(byte ch_value)
{
  for (int i=1; i <= 512; i++)
    {
      dmx.write(i, ch_value);
    }
  dmx.update();
}

void change_some(byte color, byte ch_value)  //color is byte from 1-4  1: red  2:green   3:blue   4:white    ch_value:0-255
{
  ch_numb = color;
  
  while (ch_numb <= 512)
    {
      dmx.write(ch_numb, ch_value);
      ch_numb += 3;
    }
  dmx.update();
}
