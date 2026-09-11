#pragma once

#include "Sensors/Calibration/Algorithms/ICalibrationAlgorithm.h"

class ILidarCalibrationAlgorithm :public ICalibrationAlgorithm
{
public:
    virtual ~ILidarCalibrationAlgorithm() = default;

    virtual bool calibrate() = 0;
};