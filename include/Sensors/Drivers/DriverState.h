#pragma once

enum class DriverState
{
    Created,
    Ready,
    Running,
    Finished,
    Error,
    Stopping,
    Stopped
};