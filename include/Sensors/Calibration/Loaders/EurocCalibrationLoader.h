#pragma once

#include "ICalibrationLoader.h"

class EurocCalibrationLoader : public ICalibrationLoader
{
public:
    std::unique_ptr<ICalibration>
    load(const std::string& file,
         const std::string& sensor_type) override;

private:
    
    //PARSES THE SENSOR SPECIFIC DATA IN ICALIBRATION FORMAT
    std::unique_ptr<ICalibration>
    loadCameraCalibration(const std::string& file);

    std::unique_ptr<ICalibration>
    loadImuCalibration(const std::string& file);
};