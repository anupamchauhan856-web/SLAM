#pragma once

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>

#include "SensorDriver.h"
#include"SensorBuffer/BufferManager.h"

#include"SensorDriverDataStructs/CameraEntry.h"
#include"SensorDriverDataStructs/ImuEntry.h"

class EurocDatasetDriver : public SensorDriver{
public:
    //CONSTRUCTOR
    //PATH OF DATASET
    //BUFFER WHERE IT WILL BE SAVED: OWN BUFFER
    //REFERENCE OF BUFFER MANAGER IS TAKEN IN CONSTRUCTOR
    //BUFFER MUST BE INIT BEFORE DRIVER IS CREATED
    EurocDatasetDriver(
        const std::string& dataset_path,
        const std::string& sensor_id,
        const std::string& sensor_type,
        const std::string& stream,
        const std::string& data_path,
        const std::string& csv,
        BufferManager& buffer_manager
    );

    //DESTRUCTOR: POLYMORPHIC OVERRIDE
    ~EurocDatasetDriver() override = default;

    //INIT: CHECK DATAPATH AND CSV, READ METADATA AND PREPARE INDICES
    bool init() override;

    //START: START DATASET PLATBACK AND BUFFER FEED
    bool start() override;

    //STOP: STOP PLAYBACK, RELEASE RESOURCES, MARK DRIVER AS STOPPED
    bool stop() override;

    //LOAD AND PUBLIHS SENSOR DATA
    bool loadCameraCsv(
        const std::string& csv_path,
        std::vector<CameraEntry>& entries
    );

    bool loadImuCsv(
        const std::string& csv_path,
        std::vector<ImuEntry>& entries
    );

    bool loadCameraFrame(
        const CameraEntry& entry,
        const std::string& camera_path,
        uint32_t camera_id
    );

    bool publishImu(
        const ImuEntry& entry
    );

private:
    std::string dataset_path_;

    std::string sensor_id_;
    std::string sensor_type_;
    std::string stream_;
    std::string data_path_;
    std::string csv_;

    BufferManager& buffer_manager_;
};