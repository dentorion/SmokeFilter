#pragma once

#include "DisplayRenderer.h"

class Screen;

class DisplayManager
{
public:
    bool begin();

    void show(Screen& screen);

    DisplayRenderer& renderer();

private:
    DisplayRenderer _renderer;
};