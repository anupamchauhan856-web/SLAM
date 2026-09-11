//USED FOR CALIBRATION MANAGER 
//FOR CALIBRATING EACH SENSOR IT NEEDS ITS DETAILS
//PASSED AS PARAMETER

#pragma once

#include <string>

struct CalibrationConfig
{
    std::string sensorId;
    std::string sensorType;

    // Type of provider: loader / algorithm
    std::string providerType;

    // Specific provider: euroc_yaml / zhang / stereo
    std::string provider;

    // Input file, if required by the provider
    std::string file;
};