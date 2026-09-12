#include "Sensors/Drivers/DataSources/EurocCameraSource.h"

#include <fstream>
#include <sstream>

#include <opencv2/imgcodecs.hpp>

EurocCameraSource::EurocCameraSource(
    const std::string& dataset_path,
    const std::string& sensor_id,
    const std::string& data_path,
    const std::string& csv)
    : dataset_path_(dataset_path),
      sensor_id_(sensor_id),
      data_path_(data_path),
      csv_(csv)
{
}

bool EurocCameraSource::loadCsv()
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

        std::string timestamp;
        std::string filename;

        if (!std::getline(ss, timestamp, ','))
            continue;

        if (!std::getline(ss, filename, ','))
            continue;

        if (!filename.empty() &&
            filename.back() == '\r')
        {
            filename.pop_back();
        }

        CameraEntry entry;

        entry.timestamp =
            std::stoll(timestamp);

        entry.filename =
            filename;

        entries_.push_back(
            std::move(entry));
    }

    return !entries_.empty();
}

bool EurocCameraSource::init()
{
    current_index_ = 0;

    return loadCsv();
}

bool EurocCameraSource::readNext(
    BufferManager::Data& data)
{
    if (isFinished())
        return false;

    const CameraEntry& entry =
        entries_[current_index_];

    const std::string image_path =
        dataset_path_ + "/" +
        data_path_ + "/" +
        entry.filename;

    cv::Mat image =
        cv::imread(
            image_path,
            cv::IMREAD_GRAYSCALE);

    if (image.empty())
        return false;

    CameraData camera_data;

    camera_data.sensor_id =
        sensor_id_;

    camera_data.timestamp =
        entry.timestamp;

    camera_data.image =
        std::move(image);

    data =
        std::move(camera_data);

    ++current_index_;

    return true;
}

bool EurocCameraSource::isFinished() const
{
    return current_index_ >= entries_.size();
}