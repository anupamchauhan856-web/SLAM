#pragma once

#include <atomic>
#include <memory>
#include <thread>

#include "IDataPlayer.h"
#include "PlaybackConfig.h"

#include "Sensors/Drivers/DataSources/IDataSource.h"
#include "Sensors/Buffers/BufferManager.h"

class DatasetPlayer : public IDataPlayer
{
public:

    DatasetPlayer(
        std::unique_ptr<IDataSource> source,
        BufferManager& buffer_manager,
        const PlaybackConfig& config);

    ~DatasetPlayer() override;

    bool start() override;
    bool stop() override;

    bool isRunning() const override;

private:

    void playbackLoop();

private:

    std::unique_ptr<IDataSource> source_;

    BufferManager& buffer_manager_;

    PlaybackConfig config_;

    std::thread playback_thread_;

    std::atomic<bool> running_{false};

    std::atomic<bool> finished_{false};

    std::atomic<bool> error_{false};
};