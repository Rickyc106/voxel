#pragma once

#include <math.h>
#include <vector>
#include <Adafruit_Sensor.h>

#define MS_TO_SEC 1000
#define RAD_TO_DEG 180 / M_PI

namespace utils
{
    /*3-Axis Value Type*/
    struct Euler
    {
        double x, y, z;

        Euler() : x(0.0), y(0.0), z(0.0)
        {
        }
    };

    /*6-Axis Orientation Estimate*/
    struct Orientation
    {
        Euler angle;
        Euler rate;

        Orientation()
        {
        }
    };

    /**
     * Implements a basic low-pass filter via
     * exponentially weighted moving average.
     * 
     * Uses a single constant, alpha, to weight
     * ratio of filtering
     */
    class ComplementaryFilter
    {
    private:
        Orientation filtered_state;
        double alpha;
        double timestep_ms;

    protected:
        Euler calculateAngleForGyro(const sensors_event_t& sensor)
        {
            Euler result;
            result.x = sensor.gyro.x * (timestep_ms / MS_TO_SEC) * RAD_TO_DEG % 360;
            result.y = sensor.gyro.y * (timestep_ms / MS_TO_SEC) * RAD_TO_DEG % 360;
            result.z = sensor.gyro.z * (timestep_ms / MS_TO_SEC) * RAD_TO_DEG % 360;

            return result;
        }

        Euler calculateAngleForAccel(const sensors_event_t& sensor)
        {
            Euler result;
            result.x = atan2(sensor.acceleration.y, sensor.acceleration.z) * RAD_TO_DEG % 360;
            result.y = atan2(sensor.acceleration.x, sensor.acceleration.z) * RAD_TO_DEG % 360;
            result.z = atan2(sensor.acceleration.x, sensor.acceleration.y) * RAD_TO_DEG % 360;

            return result;
        }

    public:
        ComplementaryFilter(const double& alpha = 0.98, const double& dt = 100) : alpha(alpha), timestep_ms(dt)
        {
        }

        ~ComplementaryFilter()
        {
        }

        /*Update orientation via fusion of gyro and accelerometer data*/
        Orientation update(const sensors_event_t& gyro, const sensors_event_t& accel)
        {
            Euler gyro_angle = calculateAngleForGyro(gyro);
            Euler accel_angle = calculateAngleForAccel(accel);

            filtered_state.angle.x = alpha * (filtered_state.angle.x + gyro_angle.x) + (1 - alpha) * accel_angle.x;
            filtered_state.angle.y = alpha * (filtered_state.angle.y + gyro_angle.y) + (1 - alpha) * accel_angle.y;
            filtered_state.angle.z = alpha * (filtered_state.angle.z + gyro_angle.z) + (1 - alpha) * accel_angle.z;

            return filtered_state;
        }

        /*Update orientation via fusion of gyro, accelerometer and magnetometer data*/
        Orientation update(const sensors_event_t& gyro, const sensors_event_t& accel, const sensors_event_t& mag)
        {
            // TODO implement
        }
    };

} // End namespace utils