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

        // Dataset configuration
        if (!config["dataset"])
        {
            std::cerr << "Error: dataset configuration missing\n";
            return false;
        }

        const std::string dataset_path =
            config["dataset"]["path"].as<std::string>();

        // Sensor configuration
        if (!config["sensors"] || !config["sensors"].IsSequence())
        {
            std::cerr << "Error: sensors configuration missing\n";
            return false;
        }

        for (const auto& sensor_node : config["sensors"])
        {
            const std::string id =
                sensor_node["id"].as<std::string>();

            const std::string type =
                sensor_node["type"].as<std::string>();

            const std::string source =
                sensor_node["source"].as<std::string>();

            const std::string driver =
                sensor_node["driver"].as<std::string>();

            // Currently support EuRoC dataset sensors only
            if (source != "dataset" || driver != "euroc")
            {
                std::cerr << "Unsupported source/driver for sensor: "
                          << id << '\n';
                return false;
            }

            const YAML::Node sensor_config =
                sensor_node["config"];

            const std::string stream =
                sensor_config["stream"].as<std::string>();

            const std::string csv =
                sensor_config["csv"].as<std::string>();

            std::string data_path;

            if (sensor_config["data_path"])
            {
                data_path =
                    sensor_config["data_path"].as<std::string>();
            }

            // Create the EuRoC driver
            auto driver_object =
                std::make_unique<EurocDatasetDriver>(
                    dataset_path,
                    id,
                    type,
                    stream,
                    data_path,
                    csv,
                    buffer_manager_);

            // Create the common SensorContext
            auto sensor =
                std::make_unique<SensorContext>(
                    id,
                    std::move(driver_object));

            // addSensor() registers both:
            // 1. SensorContext in sensors_
            // 2. Buffer in BufferManager
            if (!addSensor(std::move(sensor)))
            {
                std::cerr << "Failed to add sensor: "
                          << id << '\n';
                return false;
            }

            // Keep track of sensor type
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
                std::cerr << "Unsupported sensor type: "
                          << type << '\n';
                return false;
            }

            std::cout << "Added sensor: "
                      << id << " (" << type << ")\n";
        }

        return true;
    }
    catch (const YAML::Exception& e)
    {
        std::cerr << "YAML error: "
                  << e.what() << '\n';

        return false;
    }
}

bool SensorManager::popNext(Data& data)
{
    return buffer_manager_.popNext(data);
}

bool SensorManager::isRunning() const
{
    for (const auto& [name, sensor] : sensors_)
    {
        if (sensor->getDriver().isRunning())
            return true;
    }

    return false;
}