#ifndef LITTLEDB_ALGORITHMS_H
#define LITTLEDB_ALGORITHMS_H

#include "Result.h"
#include "Record.h"

namespace LittleDB
{

template<typename T>
class Table;

template<typename T>
class Algorithms
{
public:

    explicit Algorithms(Table<T>& table);

    template<typename Predicate>
    Result findIf(Predicate predicate,
                  Record<T>& result);

    template<typename Predicate>
    uint32_t countIf(Predicate predicate);

    template<typename Predicate>
    Result updateIf(Predicate predicate,
                    const T& data);

    template<typename Predicate>
    uint32_t removeIf(Predicate predicate);

    template<typename Predicate>
    bool anyOf(Predicate predicate);

    template<typename Predicate>
    bool allOf(Predicate predicate);

    template<typename Predicate>
    bool noneOf(Predicate predicate);

private:

    Table<T>& _table;
};

}

#include "Algorithms.tpp"

#endif