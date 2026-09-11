#include "Sensors/Calibration/Manager/CalibrationManager.h"

#include "Sensors/Calibration/Loaders/ICalibrationLoader.h"
#include "Sensors/Calibration/Loaders/EurocCalibrationLoader.h"

#include <stdexcept>

std::unique_ptr<ICalibrationLoader>
CalibrationManager::createLoader(const std::string& provider)
{
    if (provider == "euroc_yaml")
    {
        return std::make_unique<EurocCalibrationLoader>();
    }

    throw std::runtime_error(
        "Unknown calibration loader: " + provider);
}


std::unique_ptr<ICalibration>
CalibrationManager::loadCalibration(
    const CalibrationConfig& config)
{
    // ---------------------------------------------------------
    // 1. Validate configuration
    // ---------------------------------------------------------

    if (config.sensorId.empty())
    {
        throw std::invalid_argument(
            "Calibration sensorId is empty");
    }

    if (config.sensorType.empty())
    {
        throw std::invalid_argument(
            "Calibration sensorType is empty for sensor: "
            + config.sensorId);
    }

    if (config.providerType.empty())
    {
        throw std::invalid_argument(
            "Calibration providerType is empty for sensor: "
            + config.sensorId);
    }

    if (config.provider.empty())
    {
        throw std::invalid_argument(
            "Calibration provider is empty for sensor: "
            + config.sensorId);
    }

    // ---------------------------------------------------------
    // 2. Currently support calibration loaders
    // ---------------------------------------------------------

    if (config.providerType != "loader")
    {
        throw std::runtime_error(
            "Unsupported calibration provider type: "
            + config.providerType);
    }

    // ---------------------------------------------------------
    // 3. File is required for loader
    // ---------------------------------------------------------

    if (config.file.empty())
    {
        throw std::invalid_argument(
            "Calibration file is empty for sensor: "
            + config.sensorId);
    }

    // ---------------------------------------------------------
    // 4. Create requested loader
    // ---------------------------------------------------------

    auto loader = createLoader(config.provider);

    // ---------------------------------------------------------
    // 5. Load sensor-specific calibration
    // ---------------------------------------------------------

    auto calibration =
        loader->load(
            config.file,
            config.sensorType);

    // ---------------------------------------------------------
    // 6. Validate result
    // ---------------------------------------------------------

    if (!calibration)
    {
        throw std::runtime_error(
            "Failed to load calibration for sensor: "
            + config.sensorId);
    }

    return calibration;
}