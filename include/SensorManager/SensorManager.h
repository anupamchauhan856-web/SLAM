#pragma once

#include<unordered_map>
#include<string>
#include<memory>
#include<vector>
#include<iostream>
#include <yaml-cpp/yaml.h>

#include"SensorContext.h"
#include"SensorBuffer/BufferManager.h"
#include"SensorDrivers/EurocDatasetDriver.h"

class SensorManager{
public:
    //LOAD CONFIGURATION FILE AND CREATE SENSOR CONTEXTS
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

private:
    //STORE ALL SENSORS AVAILABLE
    std::unordered_map<std::string,std::shared_ptr<SensorContext>> sensors_;

    //LOOKUP FOR SENSOR BY NAME
    std::vector<std::string> cameras_;
    std::vector<std::string> imus_;
    std::vector<std::string> lidars_;

    //BUFFER MANAGER: HOLDS ALL SENSOR DATA
    BufferManager buffer_manager_;
};