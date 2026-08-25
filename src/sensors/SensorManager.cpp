#include "SensorManager.h"

void SensorManager::begin()
{
    _temperature = 22.5f;
    _humidity = 45.0f;
    _airQuality = 120;
}

void SensorManager::update()
{
    // Mock.
    // Позже здесь будет чтение реальных датчиков.
}

float SensorManager::temperature() const
{
    return _temperature;
}

float SensorManager::humidity() const
{
    return _humidity;
}

uint16_t SensorManager::airQuality() const
{
    return _airQuality;
}