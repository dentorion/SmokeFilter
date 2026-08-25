#pragma once

#include <Arduino.h>

#include "LGFX.h"

class DisplayRenderer
{
public:
    bool begin();

    void clear();

    void update();

    void drawCenteredText(const String& text);

    LGFX& lcd();

private:
    LGFX _lcd;
};