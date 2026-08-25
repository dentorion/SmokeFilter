#pragma once

#include "Screen.h"
#include "../models/StatisticsScreenData.h"

class DisplayRenderer;

class StatisticsScreen : public Screen
{
public:
    void setData(const StatisticsScreenData& data);

    void draw(DisplayRenderer& renderer) override;

private:
    StatisticsScreenData _data;
};