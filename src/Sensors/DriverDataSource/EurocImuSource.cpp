#include "Sensors/Drivers/DataSources/EurocImuSource.h"

#include <fstream>
#include <sstream>

EurocImuSource::EurocImuSource(
    const std::string& dataset_path,
    const std::string& sensor_id,
    const std::string& csv)
    : dataset_path_(dataset_path),
      sensor_id_(sensor_id),
      csv_(csv)
{
}

bool EurocImuSource::loadCsv()
{
    const std::string csv_path =
        dataset_path_ + "/" + csv_;

    std::ifstream file(csv_path);

    if (!file.is_open())
        return false;

    entries_.clear();

    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;

        std::stringstream ss(line);

        std::string values[7];

        bool valid = true;

        for (int i = 0; i < 7; ++i)
        {
            if (!std::getline(ss, values[i], ','))
            {
                valid = false;
                break;
            }
        }

        if (!valid)
            continue;

        ImuEntry entry;

        entry.timestamp =
            std::stoll(values[0]);

        entry.gyro_x =
            std::stod(values[1]);

        entry.gyro_y =
            std::stod(values[2]);

        entry.gyro_z =
            std::stod(values[3]);

        entry.accel_x =
            std::stod(values[4]);

        entry.accel_y =
            std::stod(values[5]);

        entry.accel_z =
            std::stod(values[6]);

        entries_.push_back(entry);
    }

    return !entries_.empty();
}

bool EurocImuSource::init()
{
    current_index_ = 0;

    return loadCsv();
}

bool EurocImuSource::readNext(
    BufferManager::Data& data)
{
    if (isFinished())
        return false;

    const ImuEntry& entry =
        entries_[current_index_];

    ImuData imu_data;

    imu_data.sensor_id =
        sensor_id_;

    imu_data.timestamp =
        entry.timestamp;

    imu_data.gyro_x =
        entry.gyro_x;

    imu_data.gyro_y =
        entry.gyro_y;

    imu_data.gyro_z =
        entry.gyro_z;

    imu_data.accel_x =
        entry.accel_x;

    imu_data.accel_y =
        entry.accel_y;

    imu_data.accel_z =
        entry.accel_z;

    data =
        std::move(imu_data);

    ++current_index_;

    return true;
}

bool EurocImuSource::isFinished() const
{
    return current_index_ >= entries_.size();
}