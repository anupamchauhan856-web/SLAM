#pragma once

#include "Sensors/Calibration/Algorithms/ICalibrationAlgorithm.h"

class ILidarCalibrationAlgorithm :public ICalibrationAlgorithm
{
public:
    virtual ~ILidarCalibrationAlgorithm() = default;

    virtual std::unique_ptr<ICalibration>
    calibrate(const CalibrationData& data) override = 0;
};