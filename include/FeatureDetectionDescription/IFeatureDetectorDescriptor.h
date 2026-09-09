#pragma once

#include <opencv2/core.hpp>
#include <vector>

class IFeatureDetectorDescriptor{
public:
    virtual ~IFeatureDetectorDescriptor() = default;

    //IMAGE IS PASSED AS PARAMETER
    //KEYPOINTS ARE SAVED IN KEYPOINT
    //DESCRPTOR IS A SINGLE ARRAY THAT HOLDS FOR ALL KEYPOINTS
    virtual void detectAndCompute(
        const cv::Mat& image,
        std::vector<cv::KeyPoint>& keypoints,
        cv::Mat& descriptors) = 0;
};