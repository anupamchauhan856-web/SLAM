#pragma once

#include <memory>
#include <string>

#include "SensorDriver.h"

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
private:
    std::string name_;

    // WHICH DRIVER CREATED THIS CONTEXT
    std::unique_ptr<SensorDriver> driver_;
};