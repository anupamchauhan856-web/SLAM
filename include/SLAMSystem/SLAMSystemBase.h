#pragma once

#include"SensorManager.h"

class SLAMSystemBase{
public:
virtual ~SLAMSystemBase() = default;

//OVERRIDEN METHODS BY DERIVED CLASSES
virtual void init() = 0; //configure SLAM
virtual void update() = 0; //one processing step of SLAM, can be called in a loop
virtual void run() = 0; //continuous execution

protected:
std::unique_ptr<SensorManager> sensor_manager_;
};