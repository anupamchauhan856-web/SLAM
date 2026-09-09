#pragma once

#include<vector>

#include"ICalibrationProvider.h"
#include"CalibrationConfig.h"

class EurocYamlCalibration : public ICalibrationProvider{
public:
    explicit EurocYamlCalibration(const std::vector<CalibrationConfig>& configs);
    bool load(SensorContext& context) override;
    
private:
    //METHODS
    bool loadCameraCalibration(
        const CalibrationConfig& config,
        SensorContext& context);

    bool loadImuCalibration(
        const CalibrationConfig& config,
        SensorContext& context);

    //FIELDS
    std::vector<CalibrationConfig> configs_;
};