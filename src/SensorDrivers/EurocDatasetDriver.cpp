#include "SensorDrivers/EurocDatasetDriver.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

EurocDatasetDriver::EurocDatasetDriver(
    const std::string& dataset_path,
    const std::string& sensor_id,
    const std::string& sensor_type,
    const std::string& stream,
    const std::string& data_path,
    const std::string& csv,
    BufferManager& buffer_manager)
    : dataset_path_(dataset_path),
      sensor_id_(sensor_id),
      sensor_type_(sensor_type),
      stream_(stream),
      data_path_(data_path),
      csv_(csv),
      buffer_manager_(buffer_manager)
{
}

bool EurocDatasetDriver::loadCameraCsv(
    const std::string& csv_path,
    std::vector<CameraEntry>& entries)
{
    std::ifstream file(csv_path);

    if (!file.is_open())
        return false;

    entries.clear();

    std::string line;

    while (std::getline(file, line))
    {
        // Skip empty lines and comments.
        if (line.empty() || line[0] == '#')
            continue;

        std::stringstream ss(line);

        std::string timestamp;
        std::string filename;

        if (!std::getline(ss, timestamp, ','))
            continue;

        if (!std::getline(ss, filename, ','))
            continue;

        CameraEntry entry;

        entry.timestamp = std::stoll(timestamp);
        entry.filename = filename;

        entries.push_back(entry);
    }

    return !entries.empty();
}

bool EurocDatasetDriver::loadImuCsv(
    const std::string& csv_path,
    std::vector<ImuEntry>& entries)
{
    std::ifstream file(csv_path);

    if (!file.is_open())
        return false;

    entries.clear();

    std::string line;

    while (std::getline(file, line))
    {
        // Skip empty lines and comments.
        if (line.empty() || line[0] == '#')
            continue;

        std::stringstream ss(line);

        std::string timestamp;
        std::string gyro_x;
        std::string gyro_y;
        std::string gyro_z;
        std::string accel_x;
        std::string accel_y;
        std::string accel_z;

        if (!std::getline(ss, timestamp, ','))
            continue;

        if (!std::getline(ss, gyro_x, ','))
            continue;

        if (!std::getline(ss, gyro_y, ','))
            continue;

        if (!std::getline(ss, gyro_z, ','))
            continue;

        if (!std::getline(ss, accel_x, ','))
            continue;

        if (!std::getline(ss, accel_y, ','))
            continue;

        if (!std::getline(ss, accel_z, ','))
            continue;

        ImuEntry entry;

        entry.timestamp = std::stoll(timestamp);

        entry.gyro_x = std::stod(gyro_x);
        entry.gyro_y = std::stod(gyro_y);
        entry.gyro_z = std::stod(gyro_z);

        entry.accel_x = std::stod(accel_x);
        entry.accel_y = std::stod(accel_y);
        entry.accel_z = std::stod(accel_z);

        entries.push_back(entry);
    }

    return !entries.empty();
}

bool EurocDatasetDriver::loadCameraFrame(
    const CameraEntry& entry,
    const std::string& camera_path,
    uint32_t camera_id)
{
    std::string imagePath =camera_path + "/" + entry.filename;
    std::cout << "Loading image: " << imagePath << std::endl;
    cv::Mat image =cv::imread(imagePath, cv::IMREAD_GRAYSCALE);
    if (image.empty()) return false;
    CameraData data;
    data.sensor_id ="cam" + std::to_string(camera_id);
    data.timestamp =entry.timestamp;
    data.image =image;
    return buffer_manager_.push(std::move(data));
}

bool EurocDatasetDriver::publishImu(
    const ImuEntry& entry)
{
    ImuData data;

    data.sensor_id = "imu0";

    data.timestamp = entry.timestamp;

    data.gyro_x = entry.gyro_x;
    data.gyro_y = entry.gyro_y;
    data.gyro_z = entry.gyro_z;

    data.accel_x = entry.accel_x;
    data.accel_y = entry.accel_y;
    data.accel_z = entry.accel_z;

    return buffer_manager_.push(std::move(data));
}

bool EurocDatasetDriver::init()
{
    if (!std::filesystem::exists(dataset_path_))
        return false;

    return true;
}

bool EurocDatasetDriver::start()
{
    const std::string csv_path =
        dataset_path_ + "/" + csv_;

    if (sensor_type_ == "camera")
    {
        std::vector<CameraEntry> entries;

        if (!loadCameraCsv(csv_path, entries))
            return false;

        uint32_t camera_id = 0;

        if (sensor_id_ == "cam1")
            camera_id = 1;

        const std::string camera_path =
            dataset_path_ + "/" + data_path_;

        for (const auto& entry : entries)
        {
            if (!loadCameraFrame(
                    entry,
                    camera_path,
                    camera_id))
            {
                return false;
            }
        }
    }
    else if (sensor_type_ == "imu")
    {
        std::vector<ImuEntry> entries;

        if (!loadImuCsv(csv_path, entries))
            return false;

        for (const auto& entry : entries)
        {
            if (!publishImu(entry))
                return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}

bool EurocDatasetDriver::stop()
{
    return true;
}