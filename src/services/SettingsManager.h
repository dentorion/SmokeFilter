#pragma once

#include "../config/AppSettings.h"

class SettingsManager
{
public:
    void begin();

    void load();

    void save();

    AppSettings& settings();

private:
    AppSettings _settings;
};