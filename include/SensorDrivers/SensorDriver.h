#pragma once

//INTERFACE FOR ALL SENSOR DRIVERS
class SensorDriver{
public:
    virtual ~SensorDriver() = default;

    virtual bool init() = 0;
    virtual bool start() = 0;
    virtual bool stop() = 0;
};