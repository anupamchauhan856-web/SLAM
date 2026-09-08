#pragma once

#include"CalibrationType.h"
#include"SensorContext.h"  

class SensorCalibration{
public:
    virtual ~SensorCalibration() = default;
    virtual bool calibrate(SensorContext& context) = 0;
    virtual CalibrationType type() const = 0;
};