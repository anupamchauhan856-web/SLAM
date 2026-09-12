#pragma once

#include "Sensors/Calibration/Algorithms/ICalibrationAlgorithm.h"

class ICameraCalibrationAlgorithm :public ICalibrationAlgorithm
{
public:
    virtual ~ICameraCalibrationAlgorithm() = default;

    virtual std::unique_ptr<ICalibration>
    calibrate(const CalibrationData& data) override = 0;
};