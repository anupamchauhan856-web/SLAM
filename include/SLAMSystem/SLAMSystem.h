#pragma once

#include"SensorManager/SensorManager.h"
#include "Visualization/Visualizer.h"
#include "Frontend/Frontend.h"

class Backend;
class Estimator;
class LoopClosure;

class SLAMSystem{
public:
    virtual ~SLAMSystem() = default;

    //OVERRIDEN METHODS BY DERIVED CLASSES
    virtual void init() = 0; //configure SLAM
    virtual void update() = 0; //one processing step of SLAM, can be called in a loop
    virtual void run() = 0; //continuous execution
    virtual void shutdown() = 0;

protected:
    std::unique_ptr<SensorManager> sensor_manager_;
    std::unique_ptr<Visualizer> visualizer_;
    std::unique_ptr<Frontend> frontend_;
    std::unique_ptr<Backend> backend_;
    std::unique_ptr<Estimator> estimator_;
    std::unique_ptr<LoopClosure> loop_closure_;
};