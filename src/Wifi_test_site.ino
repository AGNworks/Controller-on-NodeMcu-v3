#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

/*
const char index_html[] PROGMEM = {};
const char style_css[] PROGMEM = {};
*/

const char index_html[] PROGMEM = {"<!DOCTYPE html>\n    <html>\n        <head>\n            <link rel=\"stylesheet\" href=\"styles.css\">\n            <title>Page Title</title>\n        </head>\n        <body>\n            <h1>This is a Heading</h1>\n            <p>This is a paragraph.</p>\n        </body>\n    </html>"};
const char style_css[] PROGMEM = {"body {\n    background-color: rgb(180, 200, 202);\n  }\n  h1 {\n    color: rgb(0, 0, 109);\n  }\n  p {\n    color: rgb(2, 111, 82);\n  }"};

#ifndef APSSID
/* Set these to your desired credentials. */
#define APSSID "AGN"
#define APPSK  "12344321"
#endif


const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/


void handleRoot() {
  server.send_P(200, "text/html", index_html);
}

void handleCss() {
  server.send_P(200, "text/css", style_css);
}


void setup() {
  delay(1000);

  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  server.on("/", handleRoot);
  server.on("/styles.css", handleCss);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
