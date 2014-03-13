/**
 * Light Control with Walgreens Living Solutions controllers
 * 
 * Example using LSLight library by Steve McDonnell
**/
#include <LSLight.h>
#include <RCSwitch.h>

static LSLight light = LSLight();

void setup(void) {
    Serial.begin(115200);
    Serial.println("Initialize and turn lights off ...");
    light.init(5, OFF);
    delay(3000);
}

void loop(void) {
    Serial.print("Lamp 1 On...");
    light.on(1);
    delay(3000);
    Serial.print("Lamp 2 On...");
    light.on(2);
    delay(3000);
    Serial.println("Lamp 3 On...");
    light.on(3);
    delay(3000);
    Serial.println("All lamps off...");
    light.all(OFF);
    delay(3000);
    Serial.println("All lamps on...");
    light.all(ON);
    delay(3000);
    Serial.print("Lamp 3 Off...");
    light.off(3);
    delay(3000);
    Serial.print("Lamp 2 Off...");
    light.off(2);
    delay(3000);
    Serial.print("Lamp 1 Off...");
    light.off(1);
    delay(3000);
    Serial.println("Back on again");
    light.all(ON);
    delay(3000);
}    
