#include "EurocYamlCalibration.h"
#include "SensorContext.h"

#include <yaml-cpp/yaml.h>
#include <iostream>

//CONSTRUCTOR
EurocYamlCalibration::EurocYamlCalibration(const std::vector<CalibrationConfig>& configs)
    : configs_(configs){}

bool EurocYamlCalibration::load(SensorContext& context)
{
    for (const auto& config : configs_)
    {
        // Only process sensors explicitly requesting
        // the EuRoC YAML calibration provider.
        if (config.provider != "euroc_yaml") continue;
        if (config.sensorType == "camera")
        {
            if (!loadCameraCalibration(config, context))
            {
                std::cerr
                    << "Failed to load calibration for "
                    << config.sensorId
                    << std::endl;

                return false;
            }
        }
        else if (config.sensorType == "imu")
        {
            if (!loadImuCalibration(config, context))
            {
                std::cerr
                    << "Failed to load calibration for "
                    << config.sensorId
                    << std::endl;

                return false;
            }
        }
        else
        {
            std::cerr
                << "Unsupported sensor type: "
                << config.sensorType
                << std::endl;

            return false;
        }
    }

    return true;
}

bool EurocYamlCalibration::loadCameraCalibration(const CalibrationConfig& config, 
    SensorContext& context)
{
    try
    {
        YAML::Node yaml =YAML::LoadFile(config.file);
        if (!yaml["camera_model"])
        {
            std::cerr<< "Missing camera_model in "<< config.file<< std::endl;
            return false;
        }

        if (!yaml["intrinsics"])
        {
            std::cerr
                << "Missing intrinsics in "
                << config.file
                << std::endl;

            return false;
        }

        if (!yaml["distortion_coefficients"])
        {
            std::cerr
                << "Missing distortion_coefficients in "
                << config.file
                << std::endl;

            return false;
        }

        CameraCalibration calibration;
        calibration.model =yaml["camera_model"].as<std::string>();

        const auto intrinsics =yaml["intrinsics"];

        for (const auto& value : intrinsics)
        {
            calibration.intrinsics.push_back(value.as<double>());
        }

        const auto distortion =
            yaml["distortion_coefficients"];

        for (const auto& value : distortion)
        {
            calibration.distortion.push_back(
                value.as<double>());
        }

        if (yaml["resolution"])
        {
            calibration.width =
                yaml["resolution"][0].as<int>();

            calibration.height =
                yaml["resolution"][1].as<int>();
        }

        context.setCameraCalibration(
            config.sensorId,
            calibration);

        return true;
    }
    catch (const YAML::Exception& e)
    {
        std::cerr
            << "YAML error while reading "
            << config.file
            << ": "
            << e.what()
            << std::endl;

        return false;
    }
}