#include "Visualization/PangolinVisualizer.h"

PangolinVisualizer::PangolinVisualizer() = default;

PangolinVisualizer::~PangolinVisualizer()
{
    stop();
}

bool PangolinVisualizer::init()
{
    return true;
}

bool PangolinVisualizer::start()
{
    if (running_)
        return false;

    running_ = true;

    visualization_thread_ =
        std::thread(&PangolinVisualizer::visualizationLoop, this);

    return true;
}

bool PangolinVisualizer::stop()
{
    running_ = false;

    if (visualization_thread_.joinable())
        visualization_thread_.join();

    return true;
}

void PangolinVisualizer::updateCameraPose(
    const Eigen::Matrix4d& pose)
{
    std::lock_guard<std::mutex> lock(mutex_);
    current_pose_ = pose;
}

void PangolinVisualizer::updateTrajectory(
    const Eigen::Matrix4d& pose)
{
    std::lock_guard<std::mutex> lock(mutex_);
    trajectory_.push_back(pose);
}

void PangolinVisualizer::visualizationLoop()
{
    pangolin::CreateWindowAndBind(
        "SLAM Visualization",
        1024,
        768);

    glEnable(GL_DEPTH_TEST);

    pangolin::OpenGlRenderState camera(
        pangolin::ProjectionMatrix(
            1024,
            768,
            500,
            500,
            512,
            384,
            0.1,
            1000),
        pangolin::ModelViewLookAt(
            0,
            -3,
            -3,
            0,
            0,
            0,
            pangolin::AxisY));

    pangolin::View& display =
        pangolin::CreateDisplay()
            .SetBounds(0.0, 1.0, 0.0, 1.0)
            .SetHandler(
                new pangolin::Handler3D(camera));

    while (running_ && !pangolin::ShouldQuit())
    {
        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT);

        display.Activate(camera);

        std::vector<Eigen::Matrix4d> trajectory;

        {
            std::lock_guard<std::mutex> lock(mutex_);
            trajectory = trajectory_;
        }

        glColor3f(1.0, 1.0, 1.0);

        glBegin(GL_LINE_STRIP);

        for (const auto& pose : trajectory)
        {
            glVertex3d(
                pose(0, 3),
                pose(1, 3),
                pose(2, 3));
        }

        glEnd();

        pangolin::FinishFrame();
    }

    pangolin::DestroyWindow("SLAM Visualization");
}