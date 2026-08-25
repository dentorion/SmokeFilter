#ifndef LITTLEDB_CRC32_H
#define LITTLEDB_CRC32_H

#include <stdint.h>
#include <stddef.h>

namespace LittleDB
{

class CRC32
{
public:

    static uint32_t calculate(const void* data,
                              uint32_t length);

    static uint32_t update(uint32_t crc,
                           const void* data,
                           uint32_t length);

private:

    CRC32() = delete;
};

}

#endif