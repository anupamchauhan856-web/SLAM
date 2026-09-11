#pragma once

#include<memory>

#include<Sensors/Calibration/DataStructures/ICalibration.h>
#include<Sensors/Calibration/Config/CalibrationConfig.h>
#include<Sensors/Calibration/Loaders/ICalibrationLoader.h>

class CalibrationManager
{
public:
    CalibrationManager() = default;

    std::unique_ptr<ICalibration>
    loadCalibration(const CalibrationConfig& config);

private:
    std::unique_ptr<ICalibrationLoader>
    createLoader(const std::string& provider);
};