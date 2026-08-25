#ifndef LITTLEDB_ITERATOR_H
#define LITTLEDB_ITERATOR_H

#include <Arduino.h>
#include <LittleFS.h>

#include "Result.h"
#include "Header.h"
#include "Record.h"

namespace LittleDB
{

template<typename T>
class Table;

template<typename T>
class TableIterator
{
public:

    explicit TableIterator(Table<T>& table);

    ~TableIterator();

    Result begin();

    bool next();

    const Record<T>& record() const;

    Record<T>& record();

    bool valid() const;

    void end();

private:

    bool readNext();

private:

    Table<T>& _table;

    File _file;

    uint32_t _offset;

    bool _valid;

    Record<T> _record;

    RecordHeader _header;
};

}

#include "Iterator.tpp"

#endif