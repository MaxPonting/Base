#pragma once

#include "../type/type.h"

#include <stdio.h>

namespace Base::Log
{
    enum class Type
    { 
        Message, 
        Warning, 
        Error
    }; 

#ifdef BASE_DEBUG
    static const char* const s_types[3]  = 
    {
        "Message",
        "Warning",
        "Error"
    };
#endif

    void Print(const char* const log, const Type type, const Int32 line, const char* const file)
    {
#ifdef BASE_DEBUG
        printf("[%s][%s/%d][%s]\n", s_types[(Int32)type], file, line, log);
#endif
    }
}

