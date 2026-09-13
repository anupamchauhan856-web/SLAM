#pragma once

#include <memory>

class VisualFrontend;
class IMUFrontend;
class LidarFrontend;

class Frontend
{
public:
    virtual ~Frontend();

    virtual void init() = 0;
    virtual void process() = 0;
    virtual void reset() = 0;

protected:
    std::unique_ptr<VisualFrontend> visual_frontend_;
    std::unique_ptr<IMUFrontend>    imu_frontend_;
    std::unique_ptr<LidarFrontend>  lidar_frontend_;
};