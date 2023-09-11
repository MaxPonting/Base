#include "log/log.h"

#include <stdio.h>

namespace Base::Log 
{
    static const char* const s_types[3]  = 
    {
        "Message",
        "Warning",
        "Error"
    };

    void Print(const char* const log, const Type type, const Int32 line, const char* const file)
    {
        printf("[%s][%s/%d][%s]\n", s_types[type], file, line, log);
    }
} 


