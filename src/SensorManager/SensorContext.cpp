#include "SensorManager/SensorContext.h"

SensorContext::SensorContext(const std::string& name,
    std::unique_ptr<SensorDriver> driver):name_(name),
    driver_(std::move(driver)){}

bool SensorContext::init()
{
    return driver_->init();
}

bool SensorContext::start()
{
    return driver_->start();
}

bool SensorContext::stop()
{
    return driver_->stop();
}

const std::string& SensorContext::getName() const
{
    return name_;
}