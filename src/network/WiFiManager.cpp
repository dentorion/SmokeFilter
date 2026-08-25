#include "WiFiManager.h"

void WiFiManager::begin()
{
    _connected = false;
}

void WiFiManager::update()
{
}

bool WiFiManager::connect()
{
    _connected = true;
    return _connected;
}

void WiFiManager::disconnect()
{
    _connected = false;
}

bool WiFiManager::isConnected() const
{
    return _connected;
}