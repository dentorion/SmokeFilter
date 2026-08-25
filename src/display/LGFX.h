#pragma once

#define LGFX_USE_V1

#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device
{
    lgfx::Panel_GC9A01 _panel_instance;
    lgfx::Bus_SPI _bus_instance;

public:

    LGFX()
    {
        {
            auto cfg = _bus_instance.config();

            cfg.spi_mode   = 0;
            cfg.spi_3wire  = false;

            cfg.freq_write = 40000000;
            cfg.freq_read  = 16000000;

            cfg.pin_sclk = 14;   // D5
            cfg.pin_mosi = 13;   // D7
            cfg.pin_miso = 12;   // D6
            cfg.pin_dc   = 4;    // D2

            _bus_instance.config(cfg);
            _panel_instance.setBus(&_bus_instance);
        }

        {
            auto cfg = _panel_instance.config();

            cfg.pin_cs   = 15;   // D8
            cfg.pin_rst  = 16;   // D0
            cfg.pin_busy = -1;

            cfg.memory_width  = 240;
            cfg.memory_height = 240;

            cfg.panel_width  = 240;
            cfg.panel_height = 240;

            cfg.offset_x = 0;
            cfg.offset_y = 0;

            cfg.offset_rotation = 0;

            cfg.readable = false;
            cfg.invert = true;
            cfg.rgb_order = true;
            cfg.bus_shared = false;

            _panel_instance.config(cfg);
        }

        setPanel(&_panel_instance);
    }
};