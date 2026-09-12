#pragma once

//HANDLES PLAYBACK MECHANISM
//REALTIME, RATE, PAUSE, RESUME, STOP, ETC.
class IDataPlayer
{
public:
    virtual ~IDataPlayer() = default;

    virtual bool start() = 0;
    virtual bool stop() = 0;

    virtual bool isRunning() const = 0;
    virtual bool isFinished() const = 0;
    virtual bool hasError() const = 0;
};