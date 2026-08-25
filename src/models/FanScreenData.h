#pragma once

#include "../resources/Icons.h"

struct FanScreenData
{
    bool enabled = false;

    uint8_t batteryPercent = 100;

    bool led1 = false;
    bool led2 = false;
    bool led3 = false;
    bool led4 = false;

    const char* title = "FAN";
    const char* state = "OFF";

    Icon iconOff;
    Icon iconOn;
};