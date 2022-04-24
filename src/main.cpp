#include <Arduino.h>

#ifdef ARDUINO_ESP32_DEV
/*ESP32 Dev Board Selected*/
#define BUILTIN_LED_PIN 2
#endif

void setup() {
	Serial.begin(9600);
	pinMode(BUILTIN_LED_PIN, OUTPUT);
}

void loop() {
	digitalWrite(BUILTIN_LED_PIN, HIGH);
	delay(1000);
	
	digitalWrite(BUILTIN_LED_PIN, LOW);
	delay(1000);
}