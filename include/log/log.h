#pragma once

#include "../type/type.h"

#include <stdio.h>

namespace Base::Log
{
    typedef enum  
    { 
        TYPE_MESSAGE, 
        TYPE_WARNING, 
        TYPE_ERROR 
    } Type; 

#ifdef DEBUG
    static const char* const s_types[3]  = 
    {
        "Message",
        "Warning",
        "Error"
    };
#endif

    void Print(const char* const log, const Type type, const Int32 line, const char* const file)
    {
#ifdef DEBUG
        printf("[%s][%s/%d][%s]\n", s_types[type], file, line, log);
#endif
    }
}

