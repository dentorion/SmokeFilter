#ifndef LITTLEDB_TABLE_H
#define LITTLEDB_TABLE_H

#include <Arduino.h>
#include <LittleFS.h>

#include "Result.h"
#include "Header.h"
#include "Record.h"

namespace LittleDB
{

class Storage;

template<typename T>
class TableIterator;

template<typename T>
class Algorithms;

enum class TableState : uint8_t
{
    Closed,
    Ready,
    Corrupted
};

template<typename T>
class Table
{
public:

    Table(Storage& storage,
          const char* path);

    Result open();

    void close();

    bool isOpen() const;

    TableState state() const;

    Result insert(const T& data,
                  uint32_t& id);

    Result get(uint32_t id,
               Record<T>& record);

    Result update(uint32_t id,
                  const T& data);

    Result remove(uint32_t id);

    Result clear();

    Result compact();

    bool exists(uint32_t id);

    uint32_t activeCount() const;

    uint32_t deletedCount() const;

    uint32_t nextId() const;

    uint16_t recordSize() const;

    uint32_t fileSize() const;

    bool empty() const;

    TableIterator<T> iterator();

    Algorithms<T> algorithms();

private:

    friend class TableIterator<T>;

    struct RecordLocation
    {
        uint32_t offset;
        RecordHeader header;
    };

    Result create();

    Result readHeader();

    Result writeHeader();

    Result validate();

    Result findRecord(uint32_t id,
                      RecordLocation& location);

    Result writeRecord(File& file,
                       uint32_t id,
                       const T& data);

    Result readRecord(File& file,
                      const RecordHeader& header,
                      Record<T>& record);

    uint32_t firstRecordOffset() const;

private:

    Storage& _storage;

    const char* _path;

    TableHeader _header;

    TableState _state;
};

}

#include "Table.tpp"

#endif