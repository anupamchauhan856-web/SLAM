#pragma once

#include<unordered_map>
#include<string>
#include<memory>
#include<vector>

#include"SensorContext.h"
#include"BufferManager.h"

class SensorManager{
public:
    //ADD A SENSOR TO THE MANAGER TO THE CURRENT TYPE OF SLAM SYSTEM
    bool addSensor(std::unique_ptr<SensorContext> sensor);

    bool init();
    bool start();
    bool stop();

    std::shared_ptr<SensorContext> getSensor(const std::string& name);
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