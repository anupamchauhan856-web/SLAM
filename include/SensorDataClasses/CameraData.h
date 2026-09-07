#pragma once

#include <cstdint>

#include <opencv2/core/mat.hpp>

class CameraData{
public:
    //SENSOR MANAGER WILL USE THIS FOR MAPPING WITH SENSOR CONTEXT
    //SENSOR MANAGER WILL MAP WITH BUFFER MANAGER TO TRACK BUFFERS
    uint32_t id=0;

    int64_t timestamp=0;
    
    cv::Mat image;
};