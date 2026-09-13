#pragma once

class Estimator {
public:
    virtual ~Estimator() = default;

    virtual void init() = 0;
    virtual void predict() = 0;
    virtual void correct() = 0;
    virtual void reset() = 0;
};