#ifndef LITTLEDB_STORAGE_H
#define LITTLEDB_STORAGE_H

#include <Arduino.h>
#include <LittleFS.h>

#include "Result.h"

namespace LittleDB
{

template<typename T>
class Table;

class Storage
{
public:

    Storage();

    Result begin(bool formatOnFail = false);

    void end();

    bool mounted() const;

    template<typename T>
    Table<T> table(const char* path);

private:

    bool _mounted;
};

}

#include "Table.h"

namespace LittleDB
{

template<typename T>
Table<T> Storage::table(const char* path)
{
    return Table<T>(*this, path);
}

}

#endif