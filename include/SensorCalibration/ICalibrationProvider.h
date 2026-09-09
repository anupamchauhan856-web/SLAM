#pragma once

#include "SensorContext.h"

class ICalibrationProvider
{
public:
    virtual ~ICalibrationProvider() = default;
    virtual bool load(SensorContext& context) = 0;
};