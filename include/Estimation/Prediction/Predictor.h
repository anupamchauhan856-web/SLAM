#pragma once

#include "Estimator/State/FilterState.h"

class Predictor
{
public:
    virtual ~Predictor() = default;

    virtual void init() = 0;

    virtual FilterState predict(
        const FilterState& previous_state,
        double dt) = 0;

    virtual void reset() = 0;
};