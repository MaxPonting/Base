#pragma once

#include "../type/type.h"

#ifdef BASE_DEBUG
#include <stdio.h>
#include <stdarg.h>
#endif

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

    void Print(const char* const log, const Type type, const Int32 line, const char* const file, ...)
    {
#ifdef BASE_DEBUG
        printf("[%s][%s/%d][", s_types[(Int32)type], file, line);
        va_list argumentList;
        va_start(argumentList, file);
        vprintf(log, argumentList);
        printf("]\n");
#endif
    }
}

