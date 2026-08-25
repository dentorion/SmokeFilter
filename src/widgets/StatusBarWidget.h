#pragma once

#include <stdint.h>

class DisplayRenderer;

class StatusBarWidget
{
public:
    void draw(
        DisplayRenderer& renderer,
        bool led1,
        bool led2,
        bool led3,
        bool led4
    );
};