#include "Sensors/Drivers/Players/DatasetPlayer.h"

#include <chrono>
#include <thread>
#include <utility>

DatasetPlayer::DatasetPlayer(
    std::unique_ptr<IDataSource> source,
    BufferManager& buffer_manager,
    const PlaybackConfig& config)
    : source_(std::move(source)),
      buffer_manager_(buffer_manager),
      config_(config)
{
}

DatasetPlayer::~DatasetPlayer()
{
    stop();
}

bool DatasetPlayer::start()
{
    if (running_)
        return false;

    if (!source_)
        return false;

    running_ = true;
    finished_ = false;
    error_ = false;

    playback_thread_ =
        std::thread(
            &DatasetPlayer::playbackLoop,
            this);

    return true;
}

bool DatasetPlayer::stop()
{
    if (!running_)
    {
        if (playback_thread_.joinable())
            playback_thread_.join();

        return true;
    }

    running_ = false;

    if (playback_thread_.joinable())
        playback_thread_.join();

    return true;
}

void DatasetPlayer::playbackLoop()
{
    while (running_)
    {
        if (source_->isFinished())
        {
            finished_ = true;
            running_ = false;
            return;
        }

        BufferManager::Data data;

        if (!source_->readNext(data))
        {
            error_ = true;
            running_ = false;
            return;
        }

        bool pushed = false;

        while (running_)
        {
            if (buffer_manager_.push(data))
            {
                pushed = true;
                break;
            }

            // Buffer is currently full.
            // Do not drop sensor data.
            std::this_thread::yield();
        }

        if (!running_)
            return;

        if (!pushed)
        {
            error_ = true;
            running_ = false;
            return;
        }

        // Playback timing will be implemented here.
        //
        // For now:
        // produce as fast as the buffer allows.
    }

    running_ = false;
}

bool DatasetPlayer::isFinished() const
{
    return finished_;
}

bool DatasetPlayer::hasError() const
{
    return error_;
}