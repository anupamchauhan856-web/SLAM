#include "Sensors/Calibration/Loaders/EurocCalibrationLoader.h"
#include "Sensors/Calibration/Loaders/ICalibrationLoader.h"
#include"Sensors/Calibration/DataStructures/CameraCalibration.h"
#include"Sensors/Calibration/DataStructures/ImuCalibration.h"

#include <yaml-cpp/yaml.h>
#include <iostream>

std::unique_ptr<ICalibration>
EurocCalibrationLoader::load(
    const std::string& file,
    const std::string& sensor_type)
{
    if (sensor_type == "camera")
    {
        return loadCameraCalibration(file);
    }

    if (sensor_type == "imu")
    {
        return loadImuCalibration(file);
    }

    //TODO: LiDAR

    return nullptr;
}

//PARSE THE SENSOR YAML DATA INTO THE DATA STRUCTURE
std::unique_ptr<ICalibration>
EurocCalibrationLoader::loadCameraCalibration(
    const std::string& file)
{
    try
    {
        YAML::Node config = YAML::LoadFile(file);
        auto calibration =std::make_unique<CameraCalibration>();

        // Camera model
        if (config["camera_model"])
        {
            calibration->model =config["camera_model"].as<std::string>();
        }

        // Intrinsics: [fu, fv, cu, cv]
        if (config["intrinsics"])
        {
            const YAML::Node intrinsics = config["intrinsics"];

            if (intrinsics.size() != 4)
            {
                std::cerr
                    << "Invalid camera intrinsics in: "
                    << file << '\n';

                return nullptr;
            }

            calibration->fx =intrinsics[0].as<double>();
            calibration->fy =intrinsics[1].as<double>();
            calibration->cx =intrinsics[2].as<double>();
            calibration->cy =intrinsics[3].as<double>();
        }

        // Distortion coefficients
        if (config["distortion_coefficients"])
        {
            const YAML::Node distortion =
                config["distortion_coefficients"];

            for (const auto& value : distortion)
            {
                calibration->distortion.push_back(
                    value.as<double>());
            }
        }

        return calibration;
    }
    catch (const YAML::Exception& e)
    {
        std::cerr
            << "Failed to load camera calibration from "
            << file << ": "
            << e.what() << '\n';

        return nullptr;
    }
}

//IMU
std::unique_ptr<ICalibration>
EurocCalibrationLoader::loadImuCalibration(
    const std::string& file)
{
    try
    {
        YAML::Node config = YAML::LoadFile(file);
        auto calibration = std::make_unique<ImuCalibration>();
        if (config["gyroscope_noise_density"])
        {
            calibration->gyro_noise_density =config["gyroscope_noise_density"]
            .as<double>();
        }

        if (config["gyroscope_random_walk"])
        {
            calibration->gyro_random_walk =config["gyroscope_random_walk"]
            .as<double>();
        }

        if (config["accelerometer_noise_density"])
        {
            calibration->accel_noise_density =config["accelerometer_noise_density"]
                    .as<double>();
        }

        if (config["accelerometer_random_walk"])
        {
            calibration->accel_random_walk =config["accelerometer_random_walk"]
                    .as<double>();
        }

        return calibration;
    }
    catch (const YAML::Exception& e)
    {
        std::cerr
            << "Failed to load IMU calibration from "
            << file << ": "
            << e.what() << '\n';

        return nullptr;
    }
}