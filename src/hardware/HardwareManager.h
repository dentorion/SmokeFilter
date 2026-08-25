#pragma once

#include <stdint.h>

class HardwareManager
{
public:
    void begin();

    void update();

    void setLight(bool enabled);

    void setFan(bool enabled, uint8_t speed);

    void setRgb(bool enabled);

private:
    bool _lightEnabled = false;

    bool _fanEnabled = false;

    uint8_t _fanSpeed = 0;

    bool _rgbEnabled = false;
};