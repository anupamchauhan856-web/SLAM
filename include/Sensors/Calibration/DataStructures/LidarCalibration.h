#pragma once

#include "ICalibration.h"

#include <Eigen/Core>

class LidarCalibration : public ICalibration
{
public:
    // Transform from LiDAR frame to the reference/body frame
    Eigen::Matrix4d T_body_lidar = Eigen::Matrix4d::Identity();

    // Optional timing offset relative to system clock
    double time_offset = 0.0;
};