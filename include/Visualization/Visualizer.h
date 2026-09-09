#pragma once

#include <Eigen/Core>

class Visualizer
{
public:
    virtual ~Visualizer() = default;

    virtual bool init() = 0;
    virtual bool start() = 0;
    virtual bool stop() = 0;

    virtual void updateCameraPose(const Eigen::Matrix4d& pose) = 0;
    virtual void updateTrajectory(const Eigen::Matrix4d& pose) = 0;
};