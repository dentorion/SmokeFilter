#include "HardwareManager.h"

#include <Arduino.h>

namespace
{
    constexpr uint8_t FAN_RELAY_PIN = D3;
}

void HardwareManager::begin()
{
    _lightEnabled = false;
    _fanEnabled = false;
    _fanSpeed = 0;
    _rgbEnabled = false;

    /*
     * Начальное состояние:
     * HIGH — выключенное состояние по текущему
     * поведению подключенного реле.
     */
    digitalWrite(FAN_RELAY_PIN, HIGH);
    pinMode(FAN_RELAY_PIN, OUTPUT);
}

void HardwareManager::update()
{
}

void HardwareManager::setLight(bool enabled)
{
    _lightEnabled = enabled;
}

void HardwareManager::setFan(bool enabled, uint8_t speed)
{
    _fanEnabled = enabled;
    _fanSpeed = speed;

    /*
     * Фактическое управление реле:
     *
     * Fan ON  → HIGH
     * Fan OFF → LOW
     */
    digitalWrite(
        FAN_RELAY_PIN,
        enabled ? HIGH : LOW
    );
}

void HardwareManager::setRgb(bool enabled)
{
    _rgbEnabled = enabled;
}