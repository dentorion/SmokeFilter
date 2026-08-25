#include "CRC32.h"

namespace LittleDB
{

static constexpr uint32_t Polynomial = 0xEDB88320UL;

uint32_t CRC32::calculate(const void* data,
                          uint32_t length)
{
    return update(0xFFFFFFFFUL, data, length) ^ 0xFFFFFFFFUL;
}

uint32_t CRC32::update(uint32_t crc,
                       const void* data,
                       uint32_t length)
{
    const uint8_t* bytes = static_cast<const uint8_t*>(data);

    while (length--)
    {
        crc ^= *bytes++;

        for (uint8_t i = 0; i < 8; ++i)
        {
            if (crc & 1)
            {
                crc = (crc >> 1) ^ Polynomial;
            }
            else
            {
                crc >>= 1;
            }
        }
    }

    return crc;
}

}