#include <Arduino.h>
#include <Adafruit_FXOS8700.h>
#include <Adafruit_FXAS21002C.h>
#include <adafruit_sensor_utils.hpp>

#ifdef ARDUINO_ESP32_DEV
/*ESP32 Dev Board Selected*/
#define BUILTIN_LED_PIN 2
#endif

/* Assign a unique ID to each sensor at the same time */
Adafruit_FXAS21002C gyro = Adafruit_FXAS21002C(0x0021002C);
Adafruit_FXOS8700 accelmag = Adafruit_FXOS8700(0x8700A, 0x8700B);

void setup()
{
	Serial.begin(115200);

	if (!gyro.begin())
	{
		Serial.println("Ooops, no FXAS21002C detected ... Check your wiring!");
		while (1) {/*Don't continue to main loop*/}
	}
	else if (!accelmag.begin())
	{
		Serial.println("Ooops, no FXOS8700 detected ... Check your wiring!");
		while (1) {/*Don't continue to main loop*/}
	}

	utils::displaySensorDetails(&gyro);
	delay(500);
	utils::displaySensorDetails(&accelmag);
	delay(500);
}

void loop()
{
	sensors_event_t gevent, aevent, mevent;

	gyro.getEvent(&gevent);
	accelmag.getEvent(&aevent, &mevent);

	utils::displayEvent(gevent, utils::Event::Gyro);
	utils::displayEvent(aevent, utils::Event::Accel);
	utils::displayEvent(mevent, utils::Event::Mag);
	Serial.println("");

	delay(500);
}