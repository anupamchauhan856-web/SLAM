#pragma once

#include <memory>

class ICalibration;
class CalibrationData;

class ICalibrationAlgorithm
{
public:
    virtual ~ICalibrationAlgorithm() = default;

    virtual std::unique_ptr<ICalibration>
    calibrate(const CalibrationData& data) = 0;
};