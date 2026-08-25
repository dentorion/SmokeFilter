#pragma once

#include <stdint.h>

class DisplayRenderer;

class BatteryWidget
{
public:
    void draw(DisplayRenderer& renderer, uint8_t batteryPercent);
};