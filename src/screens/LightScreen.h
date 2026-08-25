#pragma once

#include "Screen.h"
#include "../models/LightScreenData.h"

class DisplayRenderer;

class LightScreen : public Screen
{
public:
    void setData(const LightScreenData& data);

    void draw(DisplayRenderer& renderer) override;

private:
    LightScreenData _data;
};