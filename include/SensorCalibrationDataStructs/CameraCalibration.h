//DATA IN THIS FORMAT IS SAVED IN SENSOR CONTEXT

#pragma once

#include <string>
#include <vector>

struct CameraCalibration
{
    std::string model;

    std::vector<double> intrinsics;
    std::vector<double> distortion;

    int width = 0;
    int height = 0;
};