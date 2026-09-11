#pragma once

#include "Sensors/Calibration/Algorithms/ICalibrationAlgorithm.h"

class ICameraCalibrationAlgorithm :public ICalibrationAlgorithm
{
public:
    virtual ~ICameraCalibrationAlgorithm() = default;
    virtual bool calibrate() = 0;
};