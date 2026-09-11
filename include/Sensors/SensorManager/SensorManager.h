#pragma once

#include<unordered_map>
#include<string>
#include<memory>
#include<vector>
#include<iostream>
#include <yaml-cpp/yaml.h>

#include"Sensors/SensorContext/SensorContext.h"
#include"Sensors/Buffers/BufferManager.h"
#include"Sensors/Drivers/EurocDatasetDriver.h"
#include"Sensors/Calibration/Manager/CalibrationManager.h"

class SensorManager{
public:
    //LOAD CONFIGURATION FILE AND CREATE SENSOR CONTEXTS
    //READ AND VALIDATE THE CONFIG FILE
    //IDENTIFY SENSORS AND DRIVERS AND CREATE SENSOR CONTEXTS
    //REGISTER SENSORS 
    //REGISTER SENSORS TO BUFFER MANAGER
    //CLASSIFY SENSORS ARE THEIR TYPES: CAMERA, IMU, LIDAR
    bool loadConfig(const std::string& config_path);

    //ADD A SENSOR TO THE MANAGER TO THE CURRENT TYPE OF SLAM SYSTEM
    bool addSensor(std::unique_ptr<SensorContext> sensor);

    bool init();
    bool start();
    bool stop();

    std::shared_ptr<SensorContext> getSensor(const std::string& name);

    // SENSOR DATA TYPE PROVIDED BY BUFFER MANAGER: CALL POP NEXT
    using Data = BufferManager::Data;
    bool popNext(Data& data);

    bool isRunning() const;

private:
    //STORE ALL SENSORS CONTEXTS AVAILABLE
    //SENSOR CONTEXTS WILL OWN RESPECTIVE CALIBRATION DATA
    std::unordered_map<std::string,std::shared_ptr<SensorContext>> sensors_;

    //LOOKUP FOR SENSOR BY NAME
    std::vector<std::string> cameras_;
    std::vector<std::string> imus_;
    std::vector<std::string> lidars_;

    //BUFFER MANAGER: HOLDS ALL SENSOR DATA
    BufferManager buffer_manager_;

    //CALIBRATION MANAGER
    CalibrationManager calibration_manager_;
};