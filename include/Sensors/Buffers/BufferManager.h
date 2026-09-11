//THIS CLASS WILL HOLD BUFFERS OF ALL SENSORS
//WILL BE OWNED BY SENSOR MANAGER
//SENSOR MANAGER WILL FETCH SENSOR BUFFERS BASED ON SENSOR IDs
//WILL DELIVER SENSOR DATA CHRONOLOGICALLY BASED ON TIMESTAMP
//WILL ENABLE BUFFERS ONLY FOR THE SENSORS BEING USED

#pragma once

#include <cstdint>
#include <deque>
#include <mutex>
#include <string>
#include <unordered_map>
#include <variant>

#include "SensorDataClasses/CameraData.h"
#include "SensorDataClasses/ImuData.h"

class BufferManager
{
public:

    using Data = std::variant<
        CameraData,
        ImuData
    >;

    using Buffer = std::deque<Data>;

    // Create a bounded buffer for a sensor.
    bool registerSensor(
        const std::string& sensor_id,
        std::size_t max_size);

    // Insert data into the sensor's buffer.
    bool push(Data data);

    // Remove the globally earliest timestamped measurement.
    bool popNext(Data& data);

    bool empty() const;
    std::size_t size() const;

    bool empty(
        const std::string& sensor_id) const;

    std::size_t size(
        const std::string& sensor_id) const;

private:

    struct SensorBuffer
    {
        Buffer data;
        std::size_t max_size = 0;
    };

    static std::string getSensorId(
        const Data& data);

    static int64_t getTimestamp(
        const Data& data);

private:

    mutable std::mutex mutex_;

    std::unordered_map<
        std::string,
        SensorBuffer
    > buffers_;
};