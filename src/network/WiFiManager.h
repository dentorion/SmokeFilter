#pragma once

class WiFiManager
{
public:
    void begin();

    void update();

    bool connect();

    void disconnect();

    bool isConnected() const;

private:
    bool _connected = false;
};