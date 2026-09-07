#pragma once

#include "SensorDriver.h"
#include"BufferManager.h"
#include"CameraEntry.h"
#include"ImuEntry.h"

class EurocDatasetDriver : public SensorDriver{
public:
    //CONSTRUCTOR
    //PATH OF DATASET
    //BUFFER WHERE IT WILL BE SAVED: OWN BUFFER
    EurocDatasetDriver(
        const std::string& dataset_path,
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


};