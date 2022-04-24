#pragma once

#include <Arduino.h>
#include <Adafruit_FXOS8700.h>
#include <Adafruit_FXAS21002C.h>

namespace utils
{
    /*Print gyro details*/
    void displaySensorDetails(Adafruit_FXAS21002C* s)
    {
        sensor_t sensor;
        s->getSensor(&sensor);
        Serial.println("------------------------------------");
        Serial.println("GYROSCOPE");
        Serial.println("------------------------------------");
        Serial.print("Sensor:       ");
        Serial.println(sensor.name);
        Serial.print("Driver Ver:   ");
        Serial.println(sensor.version);
        Serial.print("Unique ID:    0x");
        Serial.println(sensor.sensor_id, HEX);
        Serial.print("Max Value:    ");
        Serial.print(sensor.max_value);
        Serial.println(" rad/s");
        Serial.print("Min Value:    ");
        Serial.print(sensor.min_value);
        Serial.println(" rad/s");
        Serial.print("Resolution:   ");
        Serial.print(sensor.resolution);
        Serial.println(" rad/s");
        Serial.println("------------------------------------");
        Serial.println("");
    }

    /*Print accel/mag details*/
    void displaySensorDetails(Adafruit_FXOS8700* s)
    {
        sensor_t accel, mag;
        s->getSensor(&accel, &mag);
        Serial.println("------------------------------------");
        Serial.println("ACCELEROMETER");
        Serial.println("------------------------------------");
        Serial.print("Sensor:       ");
        Serial.println(accel.name);
        Serial.print("Driver Ver:   ");
        Serial.println(accel.version);
        Serial.print("Unique ID:    0x");
        Serial.println(accel.sensor_id, HEX);
        Serial.print("Min Delay:    ");
        Serial.print(accel.min_delay);
        Serial.println(" s");
        Serial.print("Max Value:    ");
        Serial.print(accel.max_value, 4);
        Serial.println(" m/s^2");
        Serial.print("Min Value:    ");
        Serial.print(accel.min_value, 4);
        Serial.println(" m/s^2");
        Serial.print("Resolution:   ");
        Serial.print(accel.resolution, 8);
        Serial.println(" m/s^2");
        Serial.println("------------------------------------");
        Serial.println("");
        Serial.println("------------------------------------");
        Serial.println("MAGNETOMETER");
        Serial.println("------------------------------------");
        Serial.print("Sensor:       ");
        Serial.println(mag.name);
        Serial.print("Driver Ver:   ");
        Serial.println(mag.version);
        Serial.print("Unique ID:    0x");
        Serial.println(mag.sensor_id, HEX);
        Serial.print("Min Delay:    ");
        Serial.print(accel.min_delay);
        Serial.println(" s");
        Serial.print("Max Value:    ");
        Serial.print(mag.max_value);
        Serial.println(" uT");
        Serial.print("Min Value:    ");
        Serial.print(mag.min_value);
        Serial.println(" uT");
        Serial.print("Resolution:   ");
        Serial.print(mag.resolution);
        Serial.println(" uT");
        Serial.println("------------------------------------");
        Serial.println("");
    }

    /*Type identifier for sensor*/
    enum class Event { Gyro, Accel, Mag };

    /*Print current retrieved data*/
    void displayEvent(const sensors_event_t& event, const Event& type)
    {
        switch(type)
        {
        case Event::Gyro:
            Serial.print("gX: ");
            Serial.print(event.gyro.x);
            Serial.print(", ");
            Serial.print("gY: ");
            Serial.print(event.gyro.y);
            Serial.print(", ");
            Serial.print("gZ: ");
            Serial.print(event.gyro.z);
            Serial.print("  ");
            Serial.println("rad/s ");
            break;
        case Event::Accel:
            Serial.print("aX: ");
            Serial.print(event.acceleration.x, 4);
            Serial.print(", ");
            Serial.print("aY: ");
            Serial.print(event.acceleration.y, 4);
            Serial.print(", ");
            Serial.print("aZ: ");
            Serial.print(event.acceleration.z, 4);
            Serial.print("  ");
            Serial.println("m/s^2");
            break;
        case Event::Mag:
            Serial.print("mX: ");
            Serial.print(event.magnetic.x, 1);
            Serial.print(", ");
            Serial.print("mY: ");
            Serial.print(event.magnetic.y, 1);
            Serial.print(", ");
            Serial.print("mZ: ");
            Serial.print(event.magnetic.z, 1);
            Serial.print("  ");
            Serial.println("uT");
            break;
        }
    }
} // End namespace utils