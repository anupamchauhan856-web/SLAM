#include "SensorManager/SensorManager.h"

bool SensorManager::addSensor(std::unique_ptr<SensorContext> sensor)
{
    if (!sensor) return false;
    const std::string& name = sensor->getName();

    // Don't allow duplicate sensor names
    if (sensors_.find(name) != sensors_.end()) return false;

    //Create a buffer for this sensor in the buffer manager
    if (!buffer_manager_.registerSensor(name)) return false;
    sensors_.emplace(name,std::move(sensor));
    return true;
}

bool SensorManager::init()
{
    for (auto& [name, sensor] : sensors_)
    {
        if (!sensor->init()){
            std::cerr << "Failed to initialize sensor: " << name << std::endl;
            return false;
        }
    }

    return true;
}

bool SensorManager::start()
{
    for (auto& [name, sensor] : sensors_)
    {
        if (!sensor->start()){
            std::cerr << "Failed to start sensor: " << name << std::endl;
            return false;
        }
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

bool SensorManager::loadConfig(const std::string& config_path)
{
    try
    {
        YAML::Node config = YAML::LoadFile(config_path);

        // Check that sensors section exists
        if (!config["sensors"] || !config["sensors"].IsSequence())
        {
            std::cerr << "Error: 'sensors' section is missing "
                         "or is not a sequence\n";
            return false;
        }

        // Read every sensor from YAML
        for (const auto& sensor_node : config["sensors"])
        {
            // Required fields
            if (!sensor_node["id"] ||
                !sensor_node["type"] ||
                !sensor_node["source"] ||
                !sensor_node["driver"])
            {
                std::cerr << "Error: sensor is missing required fields\n";
                return false;
            }

            const std::string id     = sensor_node["id"].as<std::string>();
            const std::string type   = sensor_node["type"].as<std::string>();
            const std::string source = sensor_node["source"].as<std::string>();
            const std::string driver = sensor_node["driver"].as<std::string>();

            // Check for duplicate sensor IDs
            if (sensors_.find(id) != sensors_.end())
            {
                std::cerr << "Error: duplicate sensor id: "
                          << id << '\n';
                return false;
            }

            // --------------------------------------------------
            // Store sensor type
            // --------------------------------------------------

            if (type == "camera")
            {
                cameras_.push_back(id);
            }
            else if (type == "imu")
            {
                imus_.push_back(id);
            }
            else if (type == "lidar")
            {
                lidars_.push_back(id);
            }
            else
            {
                std::cerr << "Error: unsupported sensor type '"
                          << type << "' for sensor "
                          << id << '\n';
                return false;
            }

            // --------------------------------------------------
            // Validate source and driver
            // --------------------------------------------------

            if (source != "dataset")
            {
                std::cerr << "Error: unsupported source '"
                          << source << "' for sensor "
                          << id << '\n';
                return false;
            }

            if (driver != "euroc")
            {
                std::cerr << "Error: unsupported driver '"
                          << driver << "' for sensor "
                          << id << '\n';
                return false;
            }

            // --------------------------------------------------
            // Register buffer for this sensor
            // --------------------------------------------------

            if (!buffer_manager_.registerSensor(id))
            {
                std::cerr << "Error: failed to register buffer for "
                          << "sensor " << id << '\n';
                return false;
            }

            std::cout << "Registered sensor: "
                      << id
                      << " (" << type << ")\n";
        }

        return true;
    }
    catch (const YAML::BadFile& e)
    {
        std::cerr << "Error: could not open config file '"
                  << config_path << "': "
                  << e.what() << '\n';

        return false;
    }
    catch (const YAML::Exception& e)
    {
        std::cerr << "YAML error: "
                  << e.what() << '\n';

        return false;
    }
}