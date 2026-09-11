//IMU CALIBRATION GLOBAL DATA FORMAT

#pragma once

#include "ICalibration.h"

class ImuCalibration : public ICalibration
{
public:
    double gyro_noise_density = 0.0;
    double gyro_random_walk = 0.0;

    double accel_noise_density = 0.0;
    double accel_random_walk = 0.0;
};