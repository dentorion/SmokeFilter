#pragma once

class DisplayRenderer;

class StateWidget
{
public:
    void draw(
        DisplayRenderer& renderer,
        const char* text
    );
};