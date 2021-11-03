#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESPDMX.h>

#include "index.h"

DMXESPSerial dmx;

#ifndef APSSID
#define APSSID "DMX512"
#define APPSK  "12344321"
#endif

const char *ssid = APSSID;
const char *password = APPSK;

String type = "RGB";
long ch_value = 0;
long ch_number = 1;

ESP8266WebServer server(80);    // Go to http://192.168.4.1 in a web browser

//----------------------------------------------------------------------------handling
void handleRoot() {
  String s = MAIN_page; //html content
  server.send(200, "text/html", s);
  Serial.println("index");
}

void handleLED() {
  String ledState = "ALL OFF";
  String t_state = server.arg("LEDstate"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);
  Serial.println(t_state);
  if(t_state == "5")
  {
    change_all(255);
    ledState = "ALL ON"; //Feedback parameter
  }
  else if (t_state == "1")
  {
    change_some(1,255);
    ledState = "ALL RED"; //Feedback parameter
  }
  else if (t_state == "2")
  {
    change_some(2,255);
    ledState = "ALL GREEN"; //Feedback parameter
  }
  else if (t_state == "3")
  {
    change_some(3,255);
    ledState = "ALL BLUE"; //Feedback parameter
  }
  else if (t_state == "4")
  {
    change_some(4,255);
    ledState = "ALL WHITE"; //Feedback parameter
  }
  else if (t_state == "0")
  {
    change_all(0);
    ledState = "ALL OFF"; //Feedback parameter  
  }
  
  server.send(200, "text/plane", ledState); //Send web page
}

void handleLEDtype() {
  String led_type = server.arg("LEDtype"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);
  Serial.println(led_type);
  type = led_type;
  server.send(200, "text/plane", type);
}

void handleLEDvalue() {
  String led_value = server.arg("LEDnumber"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);
  ch_value = led_value.substring(3).toInt();
  ch_number = led_value.substring(0,3).toInt();
  /*Serial.println("number");
  Serial.println(ch_number);
  Serial.println("value");
  Serial.println(ch_value);*/
  dmx.write(ch_number, ch_value);
  dmx.update();
  server.send(200, "text/plane", led_value.substring(3));
}


//----------------------------------------------------------------------------SETUP
void setup() {
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  
  delay(1000);
  dmx.init(512);   //we will use all the 512 DMX channels
  delay(100);

  Serial.begin(9600);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  server.on("/", handleRoot);
  server.on("/setLED", handleLED);
  server.on("/settype", handleLEDtype);
  server.on("/setvalue", handleLEDvalue);

  server.begin();
  Serial.println("HTTP server started");

  change_all(0); //turning all channel off by default
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
  if (type == "RGB" && color != 4){
    for (int i = color; i<= 512; i+=3)
      {
        dmx.write(i, ch_value);
      }
    dmx.update();
  }

  if (type == "RGBW"){
    for (int i = color; i<= 512; i+=4)
      {
        dmx.write(i, ch_value);
      }
    dmx.update();
    }
}
