#pragma once

class DisplayRenderer;

class Screen
{
public:
    virtual ~Screen() = default;

    virtual void draw(DisplayRenderer& renderer) = 0;
};