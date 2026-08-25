#pragma once
#include <Arduino.h>

struct Icon {
 uint16_t width;
 uint16_t height;
 const uint16_t* pixels;
};
extern const Icon ICON_LIGHT_OFF;
extern const Icon ICON_LIGHT_ON;
extern const Icon ICON_FAN_OFF;
extern const Icon ICON_FAN_ON;
extern const Icon ICON_STATISTICS;