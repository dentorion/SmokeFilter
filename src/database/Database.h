#pragma once

#include "src/LittleDB.h"

#include "../models/Settings.h"
#include "../models/Statistics.h"

class Database
{
public:
    static bool begin();

    static LittleDB::Table<Settings>& settings();

    static LittleDB::Table<Statistics>& statistics();

private:
    static LittleDB::Storage storage;

    static LittleDB::Table<Settings> settingsTable;

    static LittleDB::Table<Statistics> statisticsTable;
};