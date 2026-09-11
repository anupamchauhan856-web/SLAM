#include"Sensors/Buffers/BufferManager.h"

#include <limits>

bool BufferManager::registerSensor(
    const std::string& sensor_id,
    std::size_t max_size)
{
    std::lock_guard<std::mutex> lock(mutex_);

    if (sensor_id.empty()) return false;
    if (max_size == 0) return false;
    if (buffers_.find(sensor_id) != buffers_.end()) return false;
    SensorBuffer buffer;
    buffer.max_size = max_size;
    buffers_.emplace(sensor_id, std::move(buffer));
    return true;
}

bool BufferManager::push(Data data)
{
    std::lock_guard<std::mutex> lock(mutex_);
    const std::string sensor_id = getSensorId(data);
    auto it = buffers_.find(sensor_id);
    if (it == buffers_.end()) return false;
    SensorBuffer& sensor_buffer = it->second;

    // Do not silently discard measurements.
    if (sensor_buffer.data.size() >= sensor_buffer.max_size) return false;
    sensor_buffer.data.push_back(std::move(data));
    return true;
}

bool BufferManager::popNext(Data& data)
{
    std::lock_guard<std::mutex> lock(mutex_);

    std::string selected_sensor;
    int64_t earliest_timestamp = std::numeric_limits<int64_t>::max();

    for (auto& [sensor_id, sensor_buffer] : buffers_)
    {
        if (sensor_buffer.data.empty()) continue;
        const int64_t timestamp = getTimestamp(sensor_buffer.data.front());

        if (timestamp < earliest_timestamp)
        {
            earliest_timestamp = timestamp;
            selected_sensor = sensor_id;
        }
    }

    if (selected_sensor.empty())
        return false;

    SensorBuffer& selected_buffer =
        buffers_.at(selected_sensor);

    data = std::move(selected_buffer.data.front());

    selected_buffer.data.pop_front();

    return true;
}

bool BufferManager::empty() const
{
    std::lock_guard<std::mutex> lock(mutex_);

    for (const auto& [sensor_id, sensor_buffer] : buffers_)
    {
        if (!sensor_buffer.data.empty())
            return false;
    }

    return true;
}

std::size_t BufferManager::size() const
{
    std::lock_guard<std::mutex> lock(mutex_);

    std::size_t total = 0;

    for (const auto& [sensor_id, sensor_buffer] : buffers_)
        total += sensor_buffer.data.size();

    return total;
}

std::string BufferManager::getSensorId(
    const Data& data)
{
    return std::visit(
        [](const auto& sensor_data)
        {
            return sensor_data.sensor_id;
        },
        data);
}

int64_t BufferManager::getTimestamp(
    const Data& data)
{
    return std::visit(
        [](const auto& sensor_data)
        {
            return sensor_data.timestamp;
        },
        data);
}