#pragma once

#include <math.h>
#include <vector>
#include <Adafruit_Sensor.h>

#define MS_TO_SEC 1000

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
        /**
         * Calculates euler angles by integrating gyroscopic data
         * @remarks
         *      Inverse rotation about y-axis produces a positive x-angle
         *      Forward rotation about x-axis produces a positive y-angle
         * @returns
         *      gyro-angle
         */
        Euler calculateAngleForGyro(const sensors_event_t& sensor) const
        {
            Euler result;
            result.x = -sensor.gyro.y * (timestep_ms / MS_TO_SEC) * RAD_TO_DEG, 180;
            result.y =  sensor.gyro.x * (timestep_ms / MS_TO_SEC) * RAD_TO_DEG, 180;
            result.z =  sensor.gyro.z * (timestep_ms / MS_TO_SEC) * RAD_TO_DEG, 180;

            return result;
        }

        /**
         * Calculates euler angles using trigonemtric relationships between accelerometer data
         * @remarks
         *      When the gravity "vector" is orthogonal to two axes, the resultant
         *      tangent inverse approaches a singularity point and may be undefined,
         *      e.g. when imu is on a perfectly flat table
         * @returns
         *      accelerometer-angle
         */
        Euler calculateAngleForAccel(const sensors_event_t& sensor) const
        {
            Euler result;
            result.x = atan2(sensor.acceleration.x, sensor.acceleration.z) * RAD_TO_DEG, 180;
            result.y = atan2(sensor.acceleration.y, sensor.acceleration.z) * RAD_TO_DEG, 180;
            result.z = atan2(sensor.acceleration.x, sensor.acceleration.y) * RAD_TO_DEG, 180;

            return result;
        }

    public:
        /**
         * Constructor
         * @param alpha: smoothing factor, must be between [0,1] range inclusive
         * @param dt: time step between samples in milliseconds
         * @returns none
         */
        ComplementaryFilter(const double& alpha = 0, const double& dt = 100) : alpha(alpha), timestep_ms(dt)
        {
            assert(alpha >= 0 && alpha <= 1);
            assert(dt > 0);
        }

        /**
         * Destructor
         * @returns none
         */
        ~ComplementaryFilter()
        {
        }

        /**
         * Fuses gyroscope and accelerometer data
         * @param gyro: gyroscopic event data
         * @param accel: acceleration event data
         * @returns fused orientation
         */
        Orientation update(const sensors_event_t& gyro, const sensors_event_t& accel)
        {
            Euler gyro_angle = calculateAngleForGyro(gyro);
            Euler accel_angle = calculateAngleForAccel(accel);

            filtered_state.angle.x = alpha * (filtered_state.angle.x + gyro_angle.x) + (1 - alpha) * accel_angle.x;
            filtered_state.angle.y = alpha * (filtered_state.angle.y + gyro_angle.y) + (1 - alpha) * accel_angle.y;
            filtered_state.angle.z = alpha * (filtered_state.angle.z + gyro_angle.z) + (1 - alpha) * accel_angle.z;

            filtered_state.rate.x = gyro.gyro.x;
            filtered_state.rate.y = gyro.gyro.y;
            filtered_state.rate.z = gyro.gyro.z;

            return filtered_state;
        }

        /**
         * Fuses gyroscope, accelerometer and magnetometer data
         * @param gyro: gyroscopic event data
         * @param accel: acceleration event data
         * @param mag: magnetic event data
         * @returns fused orientation
         */
        Orientation update(const sensors_event_t& gyro, const sensors_event_t& accel, const sensors_event_t& mag)
        {
            // TODO implement
            return Orientation();
        }
    };

} // End namespace utils