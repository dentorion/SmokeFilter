#pragma once

class DisplayRenderer;

class TitleWidget
{
public:
    void draw(
        DisplayRenderer& renderer,
        const char* text
    );
};