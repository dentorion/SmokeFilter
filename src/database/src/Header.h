#ifndef LITTLEDB_HEADER_H
#define LITTLEDB_HEADER_H

#include <stdint.h>

namespace LittleDB
{

static constexpr uint32_t TABLE_MAGIC   = 0x4C444231UL; // "LDB1"
static constexpr uint16_t TABLE_VERSION = 0x0001;

#pragma pack(push, 1)

struct TableHeader
{
    uint32_t magic;

    uint16_t version;

    uint16_t recordSize;

    uint32_t nextId;

    uint32_t activeRecords;

    uint32_t deletedRecords;
};

#pragma pack(pop)

static_assert(sizeof(TableHeader) == 20,
              "Invalid TableHeader size");

}

#endif