//DATA IN THIS FORMAT IS SAVED IN SENSOR CONTEXT

#pragma once

struct ImuCalibration
{
    double accelerometerNoiseDensity = 0.0;
    double gyroscopeNoiseDensity = 0.0;

    double accelerometerRandomWalk = 0.0;
    double gyroscopeRandomWalk = 0.0;
};