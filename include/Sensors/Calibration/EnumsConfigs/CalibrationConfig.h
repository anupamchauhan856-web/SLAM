//FOR EACH SENSOR WE PROVIDE DATA SEPARATELY TO THE CALIBRATION PROVIDER

#pragma once

#include <string>

struct CalibrationConfig
{
    std::string sensorId;
    std::string sensorType;
    std::string provider;

    std::string file;
};