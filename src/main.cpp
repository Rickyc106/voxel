#include <Arduino.h>
#include <Adafruit_FXOS8700.h>
#include <Adafruit_FXAS21002C.h>
#include <adafruit_sensor_utils.hpp>
#include <complementary_filter.hpp>

#define ALPHA_CONSTANT 0.9
#define TIMESTEP_MS 10

/* Assign a unique ID to each sensor at the same time */
Adafruit_FXAS21002C gyro = Adafruit_FXAS21002C(0x0021002C);
Adafruit_FXOS8700 accelmag = Adafruit_FXOS8700(0x8700A, 0x8700B);

utils::ComplementaryFilter filter(ALPHA_CONSTANT, TIMESTEP_MS);

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

	#ifdef DEBUG
		utils::displaySensorDetails(&gyro);
		delay(500);
		utils::displaySensorDetails(&accelmag);
		delay(500);
	#endif
}

void loop()
{
	sensors_event_t g_event, a_event, m_event;

	gyro.getEvent(&g_event);
	accelmag.getEvent(&a_event, &m_event);

	utils::Orientation state = filter.update(g_event, a_event);

	Serial.print("theta-x: ");
	Serial.print(state.angle.x);
	Serial.print(", ");
	Serial.print("theta-y: ");
	Serial.print(state.angle.y);
	Serial.print(", ");
	Serial.print("theta-z: ");
	Serial.print(state.angle.z);
	Serial.print(", ");
	Serial.print("rate-x: ");
	Serial.print(state.rate.x);
	Serial.print(", ");
	Serial.print("rate-y: ");
	Serial.print(state.rate.y);
	Serial.print(", ");
	Serial.print("rate-z: ");
	Serial.println(state.rate.z);
	Serial.println("");

	delay(TIMESTEP_MS);
}