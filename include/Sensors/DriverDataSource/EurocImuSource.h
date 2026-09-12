#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "Sensors/DriverDataSource/IDataSource.h"
#include "Sensors/DriverRawDataStruct/ImuEntry.h"

class EurocImuSource : public IDataSource
{
public:

    EurocImuSource(
        const std::string& dataset_path,
        const std::string& sensor_id,
        const std::string& csv);

    bool init() override;

    bool readNext(
        BufferManager::Data& data) override;

    bool isFinished() const override;

private:

    bool loadCsv();

private:

    std::string dataset_path_;
    std::string sensor_id_;
    std::string csv_;

    std::vector<ImuEntry> entries_;

    std::size_t current_index_ = 0;
};