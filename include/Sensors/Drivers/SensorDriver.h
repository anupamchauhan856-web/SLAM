#pragma once

#include"Sensors/Drivers/DriverState.h"

//INTERFACE FOR ALL SENSOR DRIVERS
//DEFINES LIFECYCLE CONTRACT OF A SENSOR
class SensorDriver{
public:
    virtual ~SensorDriver() = default;

    virtual bool init() = 0;
    virtual bool start() = 0;
    virtual bool stop() = 0;

    virtual bool isRunning() const = 0;
    virtual DriverState getState() const = 0;
};