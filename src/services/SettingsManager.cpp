#include "SettingsManager.h"

void SettingsManager::begin()
{
    load();
}

void SettingsManager::load()
{
    // Пока Mock.
    // Позже здесь будет загрузка из LittleFS.
}

void SettingsManager::save()
{
    // Пока Mock.
    // Позже здесь будет сохранение в LittleFS.
}

AppSettings& SettingsManager::settings()
{
    return _settings;
}