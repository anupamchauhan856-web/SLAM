#pragma once

#include "Sensors/Calibration/Algorithms/ICalibrationAlgorithm.h"

class IImuCalibrationAlgorithm : public ICalibrationAlgorithm
{
public:
    virtual ~IImuCalibrationAlgorithm() = default;

    virtual std::unique_ptr<ICalibration>
    calibrate(const CalibrationData& data) override = 0;
};