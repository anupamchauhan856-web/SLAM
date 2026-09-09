#pragma once

#include "Visualization/Visualizer.h"

#include <pangolin/pangolin.h>
#include <thread>
#include <atomic>
#include <mutex>
#include <vector>

class PangolinVisualizer : public Visualizer
{
public:
    PangolinVisualizer();
    ~PangolinVisualizer() override;

    bool init() override;
    bool start() override;
    bool stop() override;

    void updateCameraPose(const Eigen::Matrix4d& pose) override;
    void updateTrajectory(const Eigen::Matrix4d& pose) override;

private:
    void visualizationLoop();

    std::thread visualization_thread_;
    std::atomic<bool> running_{false};

    std::mutex mutex_;

    Eigen::Matrix4d current_pose_ = Eigen::Matrix4d::Identity();
    std::vector<Eigen::Matrix4d> trajectory_;
};