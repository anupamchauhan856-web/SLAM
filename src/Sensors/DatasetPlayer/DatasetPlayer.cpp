#include "Sensors/DatasetPlayer/DatasetPlayer.h"

#include <utility>


DatasetPlayer::DatasetPlayer(
    std::unique_ptr<IDataSource> source,
    BufferManager& buffer_manager,
    const PlaybackConfig& config,
    const std::string& sensor_id)
    : source_(std::move(source)),
      buffer_manager_(buffer_manager),
      config_(config),
      sensor_id_(sensor_id)
{
}


// ============================================================
// DESTRUCTOR
// ============================================================

DatasetPlayer::~DatasetPlayer()
{
    stop();
}


// ============================================================
// START
// ============================================================

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


// ============================================================
// STOP
// ============================================================

bool DatasetPlayer::stop()
{
    if (!running_)
    {
        /*
         * The thread may have already finished naturally,
         * but still needs to be joined.
         */
        if (playback_thread_.joinable())
            playback_thread_.join();

        return true;
    }

    /*
     * Tell the playback thread to stop.
     */
    running_ = false;

    /*
     * Wake it if it is blocked waiting for
     * buffer space.
     */
    buffer_manager_.notifyAll();

    /*
     * Wait until the playback thread has completely
     * terminated.
     */
    if (playback_thread_.joinable())
        playback_thread_.join();

    return true;
}


// ============================================================
// PLAYBACK LOOP
// ============================================================

void DatasetPlayer::playbackLoop()
{
    while (running_)
    {
        // ----------------------------------------------------
        // Check dataset EOF
        // ----------------------------------------------------

        if (source_->isFinished())
        {
            finished_ = true;

            /*
             * Tell BufferManager that this sensor has
             * reached the end of its dataset.
             *
             * It must no longer block the watermark.
             */
            buffer_manager_.markFinished(
                sensor_id_);

            running_ = false;

            return;
        }


        // ----------------------------------------------------
        // Read next measurement
        // ----------------------------------------------------

        BufferManager::Data data;

        if (!source_->readNext(data))
        {
            /*
             * readNext() failed before reaching normal EOF.
             * Treat this as an acquisition error.
             */
            error_ = true;

            buffer_manager_.markFinished(
                sensor_id_);

            running_ = false;

            return;
        }


        // ----------------------------------------------------
        // Publish to BufferManager
        // ----------------------------------------------------

        if (!buffer_manager_.pushBlocking(
                std::move(data),
                running_))
        {
            /*
             * Normally this happens because stop()
             * changed running_ to false.
             */
            if (running_)
            {
                error_ = true;
            }

            return;
        }


        // ----------------------------------------------------
        // Playback timing
        // ----------------------------------------------------

        /*
         * Timestamp-based realtime playback will be
         * implemented here.
         *
         * IMPORTANT:
         *
         * Sensor timestamps must NOT be modified.
         *
         * Playback rate only changes wall-clock release
         * timing.
         */
    }

    running_ = false;
}


// ============================================================
// STATUS
// ============================================================

bool DatasetPlayer::isRunning() const
{
    return running_;
}


bool DatasetPlayer::isFinished() const
{
    return finished_;
}


bool DatasetPlayer::hasError() const
{
    return error_;
}