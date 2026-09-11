//CAMERA CALIBRATION GLOBAL DATA FORMAT

#pragma once

#include "ICalibration.h"

#include <string>
#include <vector>

class CameraCalibration : public ICalibration
{
public:
    std::string model;

    double fx = 0.0;
    double fy = 0.0;
    double cx = 0.0;
    double cy = 0.0;

    std::vector<double> distortion;
};