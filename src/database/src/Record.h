#ifndef LITTLEDB_RECORD_H
#define LITTLEDB_RECORD_H

#include <stdint.h>

namespace LittleDB
{

enum class RecordState : uint8_t
{
    Empty   = 0xFF,
    Active  = 0x01,
    Deleted = 0x00
};

#pragma pack(push, 1)

struct RecordHeader
{
    uint32_t id;

    uint32_t crc32;

    uint8_t state;

    uint8_t reserved[3];
};

#pragma pack(pop)

static_assert(sizeof(RecordHeader) == 12,
              "Invalid RecordHeader size");

template<typename T>
struct Record
{
    uint32_t id;

    T data;
};

}

#endif