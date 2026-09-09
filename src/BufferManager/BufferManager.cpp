#include"SensorBuffer/BufferManager.h"

bool BufferManager::registerSensor(const std::string& sensor_id)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (buffers_.find(sensor_id) != buffers_.end()) return false;
    buffers_.emplace(sensor_id,std::deque<Data>{});
    return true;
}

bool BufferManager::push(Data data)
{
    std::lock_guard<std::mutex> lock(mutex_);

    // std::cout << "PUSH: "
    //           << getSensorId(data)
    //           << " | "
    //           << getTimestamp(data)
    //           << std::endl;

    std::string sensor_id = getSensorId(data);
    auto it = buffers_.find(sensor_id);
    if (it == buffers_.end()) return false;
    it->second.push_back(std::move(data));
    return true;
}

bool BufferManager::popNext(Data& data)
{
    std::lock_guard<std::mutex> lock(mutex_);
    std::string selected_sensor;
    int64_t earliest_timestamp = INT64_MAX;

    // Look at the FRONT of every sensor queue.
    for (auto& [sensor_id, buffer] : buffers_)
    {
        if (buffer.empty()) continue;
        const int64_t timestamp =std::visit([](const auto& value)
                {return value.timestamp;},buffer.front());

        if (timestamp < earliest_timestamp)
        {
            earliest_timestamp = timestamp;
            selected_sensor = sensor_id;
        }
    }

    // No sensor has data.
    if (selected_sensor.empty()) return false;

    // Pop from the selected sensor queue.
    auto& selected_buffer = buffers_.at(selected_sensor);

    data = std::move(selected_buffer.front());
    selected_buffer.pop_front();
    return true;
}

bool BufferManager::empty() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    for (const auto& [sensor_id, buffer] : buffers_)
    {
        if (!buffer.empty()) return false;
    }
    return true;
}

std::size_t BufferManager::size() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    std::size_t total = 0;
    for (const auto& [sensor_id, buffer] : buffers_)
    {
        total += buffer.size();
    }
    return total;
}

std::string BufferManager::getSensorId(const Data& data)
{
    return std::visit(
        [](const auto& sensorData)
        {
            return sensorData.sensor_id;
        },
        data);
}

int64_t BufferManager::getTimestamp(const Data& data)
{
    return std::visit(
        [](const auto& sensorData)
        {
            return sensorData.timestamp;
        },
        data);
}