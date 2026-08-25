#pragma once

#include <Arduino.h>

struct AppSettings
{
    uint8_t displayBrightness = 100;

    uint8_t rgbBrightness = 100;

    bool wifiEnabled = true;

    bool lightEnabled = false;

    bool fanAutoMode = true;
};