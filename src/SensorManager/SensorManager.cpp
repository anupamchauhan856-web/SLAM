#include "SensorManager.h"

bool SensorManager::addSensor(std::unique_ptr<SensorContext> sensor)
{
    if (!sensor) return false;
    const std::string& name = sensor->getName();

    // Don't allow duplicate sensor names
    if (sensors_.find(name) != sensors_.end()) return false;

    sensors_.emplace(name,std::move(sensor));

    return true;
}

bool SensorManager::init()
{
    for (auto& [name, sensor] : sensors_)
    {
        if (!sensor->init()) return false;
    }

    return true;
}

bool SensorManager::start()
{
    for (auto& [name, sensor] : sensors_)
    {
        if (!sensor->start()) return false;
    }

    return true;
}

bool SensorManager::stop()
{
    bool success = true;

    for (auto& [name, sensor] : sensors_)
    {
        if (!sensor->stop()) success = false;
    }
    return success;
}

std::shared_ptr<SensorContext>
SensorManager::getSensor(const std::string& name)
{
    auto it = sensors_.find(name);
    if (it == sensors_.end()) return nullptr;
    return it->second;
}