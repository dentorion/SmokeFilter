#ifndef LITTLEDB_TABLE_TPP
#define LITTLEDB_TABLE_TPP

#include "Storage.h"
#include "CRC32.h"
#include "Iterator.h"
#include "Algorithms.h"

namespace LittleDB
{

template<typename T>
Table<T>::Table(Storage& storage,
                const char* path)
    : _storage(storage),
      _path(path),
      _state(TableState::Closed)
{
    memset(&_header, 0, sizeof(_header));
}

template<typename T>
Result Table<T>::open()
{
    if (isOpen())
    {
        return Result::AlreadyOpen;
    }

    if (!_storage.mounted())
    {
        return Result::NotOpen;
    }

    if (!LittleFS.exists(_path))
    {
        Result result = create();

        if (result != Result::Ok)
        {
            return result;
        }
    }

    Result result = readHeader();

    if (result != Result::Ok)
    {
        _state = TableState::Corrupted;
        return result;
    }

    result = validate();

    if (result != Result::Ok)
    {
        _state = TableState::Corrupted;
        return result;
    }

    _state = TableState::Ready;

    return Result::Ok;
}

template<typename T>
void Table<T>::close()
{
    _state = TableState::Closed;
}

template<typename T>
bool Table<T>::isOpen() const
{
    return _state == TableState::Ready;
}

template<typename T>
TableState Table<T>::state() const
{
    return _state;
}

template<typename T>
Result Table<T>::create()
{
    File file = LittleFS.open(_path, "w");

    if (!file)
    {
        return Result::FileCreateError;
    }

    _header.magic = TABLE_MAGIC;
    _header.version = TABLE_VERSION;
    _header.recordSize = sizeof(T);
    _header.nextId = 1;
    _header.activeRecords = 0;
    _header.deletedRecords = 0;

    if (file.write(reinterpret_cast<const uint8_t*>(&_header),
                   sizeof(TableHeader)) != sizeof(TableHeader))
    {
        file.close();
        return Result::FileWriteError;
    }

    file.flush();
    file.close();

    return Result::Ok;
}

template<typename T>
Result Table<T>::validate()
{
    if (_header.magic != TABLE_MAGIC)
    {
        return Result::InvalidHeader;
    }

    if (_header.version != TABLE_VERSION)
    {
        return Result::InvalidHeader;
    }

    if (_header.recordSize != sizeof(T))
    {
        return Result::InvalidHeader;
    }

    File file = LittleFS.open(_path, "r");

    if (!file)
    {
        return Result::FileOpenError;
    }

    file.seek(firstRecordOffset(), SeekSet);

    RecordHeader header;
    T data;

    while (file.available())
    {
        if (file.read(reinterpret_cast<uint8_t*>(&header),
                      sizeof(header)) != sizeof(header))
        {
            file.close();
            return Result::FileReadError;
        }

        if (file.read(reinterpret_cast<uint8_t*>(&data),
                      sizeof(T)) != sizeof(T))
        {
            file.close();
            return Result::FileReadError;
        }

        if (header.state != static_cast<uint8_t>(RecordState::Active))
        {
            continue;
        }

        if (CRC32::calculate(&data, sizeof(T)) != header.crc32)
        {
            file.close();
            return Result::CRCError;
        }
    }

    file.close();

    return Result::Ok;
}

template<typename T>
Result Table<T>::readHeader()
{
    File file = LittleFS.open(_path, "r");

    if (!file)
    {
        return Result::FileOpenError;
    }

    if (file.read(reinterpret_cast<uint8_t*>(&_header),
                  sizeof(TableHeader)) != sizeof(TableHeader))
    {
        file.close();
        return Result::FileReadError;
    }

    file.close();

    return Result::Ok;
}

template<typename T>
Result Table<T>::writeHeader()
{
    File file = LittleFS.open(_path, "r+");

    if (!file)
    {
        return Result::FileOpenError;
    }

    file.seek(0, SeekSet);

    if (file.write(reinterpret_cast<const uint8_t*>(&_header),
                   sizeof(TableHeader)) != sizeof(TableHeader))
    {
        file.close();
        return Result::FileWriteError;
    }

    file.flush();
    file.close();

    return Result::Ok;
}

template<typename T>
uint32_t Table<T>::firstRecordOffset() const
{
    return sizeof(TableHeader);
}

template<typename T>
uint16_t Table<T>::recordSize() const
{
    return sizeof(T);
}

template<typename T>
uint32_t Table<T>::fileSize() const
{
    if (!isOpen())
    {
        return 0;
    }

    File file = LittleFS.open(_path, "r");

    if (!file)
    {
        return 0;
    }

    uint32_t size = file.size();

    file.close();

    return size;
}

template<typename T>
uint32_t Table<T>::activeCount() const
{
    return _header.activeRecords;
}

template<typename T>
uint32_t Table<T>::deletedCount() const
{
    return _header.deletedRecords;
}

template<typename T>
uint32_t Table<T>::nextId() const
{
    return _header.nextId;
}

template<typename T>
bool Table<T>::empty() const
{
    return _header.activeRecords == 0;
}

template<typename T>
TableIterator<T> Table<T>::iterator()
{
    return TableIterator<T>(*this);
}

template<typename T>
Algorithms<T> Table<T>::algorithms()
{
    return Algorithms<T>(*this);
}

template<typename T>
Result Table<T>::insert(const T& data,
                        uint32_t& id)
{
    if (!isOpen())
    {
        return Result::NotOpen;
    }

    File file = LittleFS.open(_path, "a");

    if (!file)
    {
        return Result::FileOpenError;
    }

    id = _header.nextId;

    Result result = writeRecord(file, id, data);

    file.close();

    if (result != Result::Ok)
    {
        return result;
    }

    ++_header.nextId;
    ++_header.activeRecords;

    return writeHeader();
}

template<typename T>
Result Table<T>::get(uint32_t id,
                     Record<T>& record)
{
    if (!isOpen())
    {
        return Result::NotOpen;
    }

    RecordLocation location;

    Result result = findRecord(id, location);

    if (result != Result::Ok)
    {
        return result;
    }

    File file = LittleFS.open(_path, "r");

    if (!file)
    {
        return Result::FileOpenError;
    }

    file.seek(location.offset + sizeof(RecordHeader), SeekSet);

    result = readRecord(file, location.header, record);

    file.close();

    return result;
}

template<typename T>
Result Table<T>::update(uint32_t id,
                        const T& data)
{
    if (!isOpen())
    {
        return Result::NotOpen;
    }

    RecordLocation location;

    Result result = findRecord(id, location);

    if (result != Result::Ok)
    {
        return result;
    }

    File file = LittleFS.open(_path, "r+");

    if (!file)
    {
        return Result::FileOpenError;
    }

    file.seek(location.offset, SeekSet);

    result = writeRecord(file, id, data);

    file.close();

    return result;
}

template<typename T>
Result Table<T>::remove(uint32_t id)
{
    if (!isOpen())
    {
        return Result::NotOpen;
    }

    RecordLocation location;

    Result result = findRecord(id, location);

    if (result != Result::Ok)
    {
        return result;
    }

    File file = LittleFS.open(_path, "r+");

    if (!file)
    {
        return Result::FileOpenError;
    }

    location.header.state = static_cast<uint8_t>(RecordState::Deleted);

    file.seek(location.offset, SeekSet);

    if (file.write(reinterpret_cast<const uint8_t*>(&location.header),
                   sizeof(RecordHeader)) != sizeof(RecordHeader))
    {
        file.close();
        return Result::FileWriteError;
    }

    file.flush();
    file.close();

    --_header.activeRecords;
    ++_header.deletedRecords;

    return writeHeader();
}

template<typename T>
bool Table<T>::exists(uint32_t id)
{
    if (!isOpen())
    {
        return false;
    }

    RecordLocation location;

    return findRecord(id, location) == Result::Ok;
}

template<typename T>
Result Table<T>::findRecord(uint32_t id,
                            RecordLocation& location)
{
    File file = LittleFS.open(_path, "r");

    if (!file)
    {
        return Result::FileOpenError;
    }

    uint32_t offset = firstRecordOffset();

    file.seek(offset, SeekSet);

    while (file.available())
    {
        RecordHeader header;

        if (file.read(reinterpret_cast<uint8_t*>(&header),
                      sizeof(RecordHeader)) != sizeof(RecordHeader))
        {
            file.close();
            return Result::FileReadError;
        }

        if (header.state == static_cast<uint8_t>(RecordState::Active) &&
            header.id == id)
        {
            location.offset = offset;
            location.header = header;

            file.close();

            return Result::Ok;
        }

        offset += sizeof(RecordHeader) + sizeof(T);
        file.seek(offset, SeekSet);
    }

    file.close();

    return Result::NotFound;
}

template<typename T>
Result Table<T>::writeRecord(File& file,
                             uint32_t id,
                             const T& data)
{
    RecordHeader header;

    header.id = id;
    header.crc32 = CRC32::calculate(&data, sizeof(T));
    header.state = static_cast<uint8_t>(RecordState::Active);
    header.reserved[0] = 0;
    header.reserved[1] = 0;
    header.reserved[2] = 0;

    if (file.write(reinterpret_cast<const uint8_t*>(&header),
                   sizeof(RecordHeader)) != sizeof(RecordHeader))
    {
        return Result::FileWriteError;
    }

    if (file.write(reinterpret_cast<const uint8_t*>(&data),
                   sizeof(T)) != sizeof(T))
    {
        return Result::FileWriteError;
    }

    file.flush();

    return Result::Ok;
}

template<typename T>
Result Table<T>::readRecord(File& file,
                            const RecordHeader& header,
                            Record<T>& record)
{
    if (file.read(reinterpret_cast<uint8_t*>(&record.data),
                  sizeof(T)) != sizeof(T))
    {
        return Result::FileReadError;
    }

    if (CRC32::calculate(&record.data, sizeof(T)) != header.crc32)
    {
        return Result::CRCError;
    }

    record.id = header.id;

    return Result::Ok;
}

template<typename T>
Result Table<T>::clear()
{
    close();

    if (LittleFS.exists(_path))
    {
        if (!LittleFS.remove(_path))
        {
            return Result::FileRemoveError;
        }
    }

    Result result = create();

    if (result != Result::Ok)
    {
        return result;
    }

    _state = TableState::Ready;

    return Result::Ok;
}

template<typename T>
Result Table<T>::compact()
{
    if (!isOpen())
    {
        return Result::NotOpen;
    }

    const char* tempPath = "/.compact.tmp";

    LittleFS.remove(tempPath);

    _header.deletedRecords = 0;

    File source = LittleFS.open(_path, "r");

    if (!source)
    {
        return Result::FileOpenError;
    }

    File target = LittleFS.open(tempPath, "w");

    if (!target)
    {
        source.close();
        return Result::FileCreateError;
    }

    if (target.write(reinterpret_cast<const uint8_t*>(&_header),
                     sizeof(TableHeader)) != sizeof(TableHeader))
    {
        source.close();
        target.close();
        LittleFS.remove(tempPath);
        return Result::FileWriteError;
    }

    source.seek(firstRecordOffset(), SeekSet);

    RecordHeader header;
    T data;

    while (source.available())
    {
        if (source.read(reinterpret_cast<uint8_t*>(&header),
                        sizeof(RecordHeader)) != sizeof(RecordHeader))
        {
            source.close();
            target.close();
            LittleFS.remove(tempPath);
            return Result::FileReadError;
        }

        if (source.read(reinterpret_cast<uint8_t*>(&data),
                        sizeof(T)) != sizeof(T))
        {
            source.close();
            target.close();
            LittleFS.remove(tempPath);
            return Result::FileReadError;
        }

        if (header.state != static_cast<uint8_t>(RecordState::Active))
        {
            continue;
        }

        if (target.write(reinterpret_cast<const uint8_t*>(&header),
                         sizeof(RecordHeader)) != sizeof(RecordHeader))
        {
            source.close();
            target.close();
            LittleFS.remove(tempPath);
            return Result::FileWriteError;
        }

        if (target.write(reinterpret_cast<const uint8_t*>(&data),
                         sizeof(T)) != sizeof(T))
        {
            source.close();
            target.close();
            LittleFS.remove(tempPath);
            return Result::FileWriteError;
        }
    }

    source.close();

    target.flush();
    target.close();

    if (!LittleFS.remove(_path))
    {
        LittleFS.remove(tempPath);
        return Result::FileRemoveError;
    }

    if (!LittleFS.rename(tempPath, _path))
    {
        return Result::FileRenameError;
    }

    return Result::Ok;
}

}

#endif