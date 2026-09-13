#pragma once

class VisualFrontend
{
public:
    virtual ~VisualFrontend() = default;

    virtual void init() = 0;
    virtual void process() = 0;
    virtual void reset() = 0;
};