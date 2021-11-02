#include <ESPDMX.h>

DMXESPSerial dmx;

void setup() {
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  dmx.init(512);                         
}

void loop() {

    dmx.write(3, 0);        
    dmx.write(1, 255);     
    dmx.update();          
    delay(1000);           
    
    dmx.write(1, 0);
    dmx.write(2, 255);
    dmx.update();
    delay(1000);

    dmx.write(2, 0);
    dmx.write(3, 255);
    dmx.update();
    delay(1000);

}
