#pragma once

#include <memory>

#include <Eigen/Core>

#include "Estimation/Estimators/Estimator.h"
#include "Estimation/States/FilterState.h"
#include "Estimator/Predictor/Predictor.h"
#include "Estimator/Corrector/Corrector.h"

class EKFEstimator : public Estimator
{
public:
    EKFEstimator(
        std::unique_ptr<Predictor> predictor,
        std::unique_ptr<Corrector> corrector);

    void init() override;
    void predict() override;
    void correct() override;
    void reset() override;

    const FilterState& getState() const;

private:
    FilterState state_;

    std::unique_ptr<Predictor> predictor_;
    std::unique_ptr<Corrector> corrector_;

    Eigen::Matrix<double, 6, 6> covariance_;
};