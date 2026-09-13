#pragma once

#include "Frontend/VisualFrontend/Pipeline/MonocularVisualFrontend.h"

class MonocularVisualFrontend : public VisualFrontend
{
public:
    ~MonocularVisualFrontend() override = default;

    void init() override;
    void process() override;
    void reset() override;

private:
    void preprocessImage();
    void detectFeatures();
    void trackFeatures();
    void matchFeatures();

    void estimateMotion();
    void validateMotion();

    void triangulate();
    void manageLandmarks();
    void manageKeyframes();
};