#pragma once

#include"SensorManager/SensorManager.h"
#include "Visualization/Visualizer.h"

class Frontend;

class SLAMSystem{
public:
    virtual ~SLAMSystem() = default;

    //OVERRIDEN METHODS BY DERIVED CLASSES
    virtual void init() = 0; //configure SLAM
    virtual void update() = 0; //one processing step of SLAM, can be called in a loop
    virtual void run() = 0; //continuous execution

protected:
    std::unique_ptr<SensorManager> sensor_manager_;
    std::unique_ptr<Visualizer> visualizer_;
    std::unique_ptr<Frontend> frontend_;
};