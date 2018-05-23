#include <Wire.h>
#include <EERAM.h>

EERAM eeram;

void setup() {
	eeram.begin();
	Serial.begin(115200);
    Serial.println(F("EERAM Test"));
    Serial.println(F("Ready for action."));
    Serial.println();
    Serial.println(F("Press (w) to write,"));
    Serial.println(F("      (r) to read, or"));
    Serial.println(F("      (c) to reconfigure"));
}

#define EERAM_SIZE (16384 / 8)

void loop() {

    int c = Serial.read();

    if (c == 'w') {
       
    	Serial.print(F("Bytewise Writing..."));
    
    	for (int i = 0; i < EERAM_SIZE; i++) {
    		eeram.write(i, i & 0xFF);
    	}
    
    	Serial.println("done");
    } else if (c == 'r') {
    	Serial.print(F("Bytewise Reading..."));
    
    	for (int i = 0; i < EERAM_SIZE; i++) {
    		uint8_t val = eeram.read(i);
    
    		if (val != (i&0xFF)) {
    			Serial.print(F("Mismatch at "));
    			Serial.print(i);
    			Serial.print(F(" ("));
    			Serial.print(val);
    			Serial.print(F(" != "));
    			Serial.print(i&0xFF);
    			Serial.println(F(")"));
    		}
    	}
    
    	Serial.println("done");
    } else if (c == 'c') {
        Serial.print(F("Configuring..."));
        eeram.end();
        eeram.begin();
        Serial.println("done");
    }

}

