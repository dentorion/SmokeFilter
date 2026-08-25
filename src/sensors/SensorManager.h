#pragma once

#include <stdint.h>

class SensorManager
{
public:
    void begin();

    void update();

    float temperature() const;
    float humidity() const;
    uint16_t airQuality() const;

private:
    float _temperature = 22.5f;
    float _humidity = 45.0f;
    uint16_t _airQuality = 120;
};