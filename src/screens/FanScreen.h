#pragma once

#include "Screen.h"
#include "../models/FanScreenData.h"

class DisplayRenderer;

class FanScreen : public Screen
{
public:
    void setData(const FanScreenData& data);

    void draw(DisplayRenderer& renderer) override;

private:
    FanScreenData _data;
};