#pragma once

#include <stdint.h>

enum class ScreenType : uint8_t
{
    Light,
    Fan,
    Statistics
};

enum class UiMode : uint8_t
{
    MainMenu,
    Statistics,
    Settings
};

struct LightState
{
    bool enabled = true;
};

struct FanState
{
    bool enabled = true;

    uint8_t speed = 0;
};

struct BatteryState
{
    uint8_t percent = 100;
};

struct WifiState
{
    bool connected = false;
};

struct SensorState
{
    float temperature = 0.0f;

    float humidity = 0.0f;

    uint16_t airQuality = 0;
};

struct StatisticsState
{
    uint32_t lightRuntimeSeconds = 0;

    uint32_t fanRuntimeSeconds = 0;

    uint32_t lightStartCount = 0;

    uint32_t fanStartCount = 0;
};

struct DeviceState
{
    LightState light;

    FanState fan;

    BatteryState battery;

    WifiState wifi;

    SensorState sensors;

    StatisticsState statistics;

    ScreenType currentScreen =
        ScreenType::Light;

    UiMode uiMode =
        UiMode::MainMenu;

    uint8_t statisticsPage = 0;
};