#pragma once

#include <vector>

#include "SensorDataClasses/CameraData.h"

class MultiviewFrame
{
public:
    std::vector<CameraData> cameras;
};