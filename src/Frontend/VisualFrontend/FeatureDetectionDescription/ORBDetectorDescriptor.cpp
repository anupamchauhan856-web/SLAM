#include "VisualFrontend/FeatureDetectionDescription/ORBDetectorDescriptor.h"

ORBDetectorDescriptor::ORBDetectorDescriptor()
{
    orb_ = cv::ORB::create();
}

void ORBDetectorDescriptor::detectAndCompute(
    const cv::Mat& image,
    std::vector<cv::KeyPoint>& keypoints,
    cv::Mat& descriptors)
{
    orb_->detectAndCompute(
        image,
        cv::noArray(),
        keypoints,
        descriptors);
}