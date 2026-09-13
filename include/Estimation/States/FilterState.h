#pragma once

#include <cstdint>

#include <Eigen/Core>
#include <Eigen/Geometry>

struct FilterState
{
    using FrameId = std::uint64_t;

    FrameId frame_id{0};
    double timestamp{0.0};

    // Camera pose expressed in the world frame.
    //
    // T_wc transforms a point from camera coordinates
    // to world coordinates:
    //
    //     p_w = T_wc * p_c
    //
    Eigen::Isometry3d T_wc =
        Eigen::Isometry3d::Identity();

    // Position of the camera in the world frame.
    Eigen::Vector3d position() const
    {
        return T_wc.translation();
    }

    // Rotation of the camera with respect to the world frame.
    Eigen::Matrix3d rotation() const
    {
        return T_wc.rotation();
    }

    // Set the complete camera pose.
    void setPose(
        const Eigen::Matrix3d& R_wc,
        const Eigen::Vector3d& t_wc)
    {
        T_wc.linear() = R_wc;
        T_wc.translation() = t_wc;
    }

    // Reset to the initial state.
    void reset()
    {
        frame_id = 0;
        timestamp = 0.0;
        T_wc.setIdentity();
    }
};