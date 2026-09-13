#pragma once

class LidarFrontend
{
public:
    virtual ~LidarFrontend() = default;

    virtual void init() = 0;
    virtual void process() = 0;
    virtual void reset() = 0;
};