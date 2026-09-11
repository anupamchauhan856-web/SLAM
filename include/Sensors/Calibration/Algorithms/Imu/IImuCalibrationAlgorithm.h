#pragma once

#include "Sensors/Calibration/Algorithms/ICalibrationAlgorithm.h"

class IImuCalibrationAlgorithm : public ICalibrationAlgorithm
{
public:
    virtual ~IImuCalibrationAlgorithm() = default;
    virtual bool calibrate() = 0;
};