#pragma once

#include <atomic>
#include <memory>
#include <string>
#include <thread>

#include "IDataPlayer.h"
#include "PlaybackConfig.h"

#include "Sensors/DriverDataSource/IDataSource.h"
#include "Sensors/Buffers/BufferManager.h"

class DatasetPlayer : public IDataPlayer
{
public:

    DatasetPlayer(
        std::unique_ptr<IDataSource> source,
        BufferManager& buffer_manager,
        const PlaybackConfig& config,
        const std::string& sensor_id);

    ~DatasetPlayer() override;

    bool start() override;
    bool stop() override;

    bool isRunning() const override;
    bool isFinished() const override;
    bool hasError() const override;

private:

    void playbackLoop();

private:

    // Data source for this sensor.
    std::unique_ptr<IDataSource> source_;

    // Shared buffer manager.
    BufferManager& buffer_manager_;

    // Playback configuration.
    PlaybackConfig config_;

    // Sensor associated with this player.
    std::string sensor_id_;

    // Playback worker thread.
    std::thread playback_thread_;

    // Thread/lifecycle state.
    std::atomic<bool> running_{false};
    std::atomic<bool> finished_{false};
    std::atomic<bool> error_{false};
};