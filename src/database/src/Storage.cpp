#include "Storage.h"

namespace LittleDB
{

Storage::Storage()
    : _mounted(false)
{
}

Result Storage::begin(bool formatOnFail)
{
    if (_mounted)
    {
        return Result::Ok;
    }

    if (LittleFS.begin())
    {
        _mounted = true;
        return Result::Ok;
    }

    if (!formatOnFail)
    {
        return Result::FileOpenError;
    }

    if (!LittleFS.format())
    {
        return Result::FileCreateError;
    }

    if (!LittleFS.begin())
    {
        return Result::FileOpenError;
    }

    _mounted = true;

    return Result::Ok;
}

void Storage::end()
{
    if (!_mounted)
    {
        return;
    }

    LittleFS.end();

    _mounted = false;
}

bool Storage::mounted() const
{
    return _mounted;
}

}