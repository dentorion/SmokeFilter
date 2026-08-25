#include "Database.h"

LittleDB::Storage Database::storage;

LittleDB::Table<Settings>
Database::settingsTable(
    storage,
    "/settings.db"
);

LittleDB::Table<Statistics>
Database::statisticsTable(
    storage,
    "/statistics.db"
);

bool Database::begin()
{
    if (storage.begin() != LittleDB::Result::Ok)
    {
        return false;
    }

    if (settingsTable.open() != LittleDB::Result::Ok)
    {
        return false;
    }

    if (statisticsTable.open() != LittleDB::Result::Ok)
    {
        return false;
    }

    return true;
}

LittleDB::Table<Settings>& Database::settings()
{
    return settingsTable;
}

LittleDB::Table<Statistics>& Database::statistics()
{
    return statisticsTable;
}