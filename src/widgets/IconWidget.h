#pragma once

#include "../resources/Icons.h"

class DisplayRenderer;

class IconWidget
{
public:
    void draw(DisplayRenderer& renderer, const Icon& icon);
};