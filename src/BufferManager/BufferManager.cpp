#include"BufferManager.h"

bool BufferManager::push(Data data)
{
    int64_t timestamp = std::visit([](const auto& value)
        {return value.timestamp;},data);
    std::lock_guard<std::mutex> lock(mutex_);
    buffer_.emplace(timestamp, std::move(data));
    return true;
}

bool BufferManager::popNext(Data& data)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (buffer_.empty()) return false;
    auto it = buffer_.begin();
    data = std::move(it->second);
    buffer_.erase(it);
    return true;
}

bool BufferManager::empty() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return buffer_.empty();
}

size_t BufferManager::size() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return buffer_.size();
}