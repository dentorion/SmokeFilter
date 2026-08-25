#ifndef LITTLEDB_ITERATOR_TPP
#define LITTLEDB_ITERATOR_TPP

#include "CRC32.h"
#include "Table.h"

namespace LittleDB
{

template<typename T>
TableIterator<T>::TableIterator(Table<T>& table)
    : _table(table),
      _offset(0),
      _valid(false)
{
}

template<typename T>
TableIterator<T>::~TableIterator()
{
    end();
}

template<typename T>
Result TableIterator<T>::begin()
{
    end();

    if (!_table.isOpen())
    {
        return Result::NotOpen;
    }

    _file = LittleFS.open(_table._path, "r");

    if (!_file)
    {
        return Result::FileOpenError;
    }

    _offset = _table.firstRecordOffset();

    _file.seek(_offset, SeekSet);

    _valid = false;

    if (readNext())
    {
        _valid = true;
        return Result::Ok;
    }

    return Result::IteratorEnd;
}

template<typename T>
bool TableIterator<T>::next()
{
    if (!_file)
    {
        _valid = false;
        return false;
    }

    return (_valid = readNext());
}

template<typename T>
const Record<T>& TableIterator<T>::record() const
{
    return _record;
}

template<typename T>
Record<T>& TableIterator<T>::record()
{
    return _record;
}

template<typename T>
bool TableIterator<T>::valid() const
{
    return _valid;
}

template<typename T>
void TableIterator<T>::end()
{
    if (_file)
    {
        _file.close();
    }

    _valid = false;
}

template<typename T>
bool TableIterator<T>::readNext()
{
    while (true)
    {
        if (!_file.available())
        {
            return false;
        }

        if (_file.read(reinterpret_cast<uint8_t*>(&_header),
                       sizeof(RecordHeader)) != sizeof(RecordHeader))
        {
            return false;
        }

        if (_file.read(reinterpret_cast<uint8_t*>(&_record.data),
                       sizeof(T)) != sizeof(T))
        {
            return false;
        }

        _offset += sizeof(RecordHeader) + sizeof(T);

        if (_header.state != static_cast<uint8_t>(RecordState::Active))
        {
            continue;
        }

        uint32_t crc = CRC32::calculate(&_record.data, sizeof(T));

        if (crc != _header.crc32)
        {
            continue;
        }

        _record.id = _header.id;

        return true;
    }
}

}

#endif