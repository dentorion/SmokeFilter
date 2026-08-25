#ifndef LITTLEDB_ALGORITHMS_TPP
#define LITTLEDB_ALGORITHMS_TPP

#include "Algorithms.h"
#include "Table.h"
#include "Iterator.h"

namespace LittleDB
{

template<typename T>
Algorithms<T>::Algorithms(Table<T>& table)
    : _table(table)
{
}

template<typename T>
template<typename Predicate>
Result Algorithms<T>::findIf(Predicate predicate,
                             Record<T>& result)
{
    TableIterator<T> it(_table);

    Result res = it.begin();

    if (res != Result::Ok)
    {
        return res;
    }

    while (it.valid())
    {
        if (predicate(it.record().data))
        {
            result = it.record();
            it.end();
            return Result::Ok;
        }

        it.next();
    }

    it.end();

    return Result::NotFound;
}

template<typename T>
template<typename Predicate>
uint32_t Algorithms<T>::countIf(Predicate predicate)
{
    TableIterator<T> it(_table);

    if (it.begin() != Result::Ok)
    {
        return 0;
    }

    uint32_t count = 0;

    while (it.valid())
    {
        if (predicate(it.record().data))
        {
            ++count;
        }

        it.next();
    }

    it.end();

    return count;
}

template<typename T>
template<typename Predicate>
Result Algorithms<T>::updateIf(Predicate predicate,
                               const T& data)
{
    TableIterator<T> it(_table);

    Result res = it.begin();

    if (res != Result::Ok)
    {
        return res;
    }

    while (it.valid())
    {
        if (predicate(it.record().data))
        {
            uint32_t id = it.record().id;

            it.end();

            return _table.update(id, data);
        }

        it.next();
    }

    it.end();

    return Result::NotFound;
}

template<typename T>
template<typename Predicate>
uint32_t Algorithms<T>::removeIf(Predicate predicate)
{
    TableIterator<T> it(_table);

    if (it.begin() != Result::Ok)
    {
        return 0;
    }

    uint32_t removed = 0;

    while (it.valid())
    {
        uint32_t id = it.record().id;

        if (predicate(it.record().data))
        {
            it.end();

            if (_table.remove(id) == Result::Ok)
            {
                ++removed;
            }

            if (it.begin() != Result::Ok)
            {
                break;
            }

            continue;
        }

        it.next();
    }

    it.end();

    return removed;
}

template<typename T>
template<typename Predicate>
bool Algorithms<T>::anyOf(Predicate predicate)
{
    return countIf(predicate) > 0;
}

template<typename T>
template<typename Predicate>
bool Algorithms<T>::allOf(Predicate predicate)
{
    TableIterator<T> it(_table);

    if (it.begin() != Result::Ok)
    {
        return false;
    }

    while (it.valid())
    {
        if (!predicate(it.record().data))
        {
            it.end();
            return false;
        }

        it.next();
    }

    it.end();

    return true;
}

template<typename T>
template<typename Predicate>
bool Algorithms<T>::noneOf(Predicate predicate)
{
    return !anyOf(predicate);
}

}

#endif