#pragma once

#include <atomic>
#include <memory>
#include <string>

#include "SensorDriver.h"

#include "Sensors/Buffers/BufferManager.h"
#include "Sensors/DatasetPlayer/DatasetPlayer.h"
#include "Sensors/DatasetPlayer/PlaybackConfig.h"
#include "Sensors/DriverDataSource/EurocCameraSource.h"
#include "Sensors/DriverDataSource/EurocImuSource.h"

class EurocDatasetDriver : public SensorDriver
{
public:

    EurocDatasetDriver(
        const std::string& dataset_path,
        const std::string& sensor_id,
        const std::string& sensor_type,
        const std::string& data_path,
        const std::string& csv,
        BufferManager& buffer_manager,
        const PlaybackConfig& playback_config);

    ~EurocDatasetDriver() override;

    bool init() override;
    bool start() override;
    bool stop() override;

    bool isRunning() const override;
    DriverState getState() const override;

private:

    bool createSource();

private:

    std::string dataset_path_;
    std::string sensor_id_;
    std::string sensor_type_;
    std::string data_path_;
    std::string csv_;

    BufferManager& buffer_manager_;

    PlaybackConfig playback_config_;

    std::unique_ptr<IDataSource> source_;

    std::unique_ptr<DatasetPlayer> player_;

    std::atomic<DriverState> state_{
        DriverState::Created
    };
};