#ifndef LITTLEDB_RESULT_H
#define LITTLEDB_RESULT_H

#include <stdint.h>

namespace LittleDB
{

enum class Result : uint8_t
{
    Ok = 0,

    NotOpen,
    AlreadyOpen,
    Corrupted,

    NotFound,
    AlreadyExists,

    InvalidArgument,
    InvalidRecord,
    InvalidHeader,

    FileOpenError,
    FileCreateError,
    FileReadError,
    FileWriteError,
    FileSeekError,
    FileRemoveError,
    FileRenameError,

    CRCError,

    NoSpace,

    IteratorEnd,

    UnknownError
};

inline bool success(Result result)
{
    return result == Result::Ok;
}

inline bool failed(Result result)
{
    return result != Result::Ok;
}

}

#endif