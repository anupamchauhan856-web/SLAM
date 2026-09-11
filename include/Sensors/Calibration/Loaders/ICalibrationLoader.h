#pragma once

#include <memory>
#include <string>

class ICalibration;

//SENSOR TYPE AND FILE PATH AS PARAMETERS
class ICalibrationLoader
{
public:
    virtual ~ICalibrationLoader() = default;

    virtual std::unique_ptr<ICalibration>
    load(const std::string& file,
         const std::string& sensor_type) = 0;
};