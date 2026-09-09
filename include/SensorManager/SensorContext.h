#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "SensorDrivers/SensorDriver.h"
#include"SensorCalibrationDataStructs/CameraCalibration.h"
#include"SensorCalibrationDataStructs/ImuCalibration.h"

class SensorContext{
public:
    //CONSTRUCTOR: NAME AND WHICH DRIVER CREATED THIS SENSOR DATA
    SensorContext(
        const std::string& name,
        std::unique_ptr<SensorDriver> driver
    );

    bool init();
    bool start();
    bool stop();

    const std::string& getName() const;

    void setCameraCalibration(
        const std::string& sensorId,
        const CameraCalibration& calibration)
    {
        cameraCalibrations_[sensorId] = calibration;
    }

    void setImuCalibration(
        const std::string& sensorId,
        const ImuCalibration& calibration)
    {
        imuCalibrations_[sensorId] = calibration;
    }
private:
    std::string name_;

    // WHICH DRIVER CREATED THIS CONTEXT
    std::unique_ptr<SensorDriver> driver_;

    //CALIBRATON DATA TO HOLD FOR EACH SENSOR
    std::unordered_map<
        std::string,
        CameraCalibration>
        cameraCalibrations_;

    std::unordered_map<
        std::string,
        ImuCalibration>
        imuCalibrations_;
};