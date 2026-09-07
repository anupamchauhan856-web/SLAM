#pragma once

#include "SensorDataClasses/CameraData.h"

class StereoFrame
{
public:
    CameraData left;
    CameraData right;
};