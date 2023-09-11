#pragma once

#include "../type/type.h"

namespace Base::Log
{
    typedef enum  
    { 
        TYPE_MESSAGE, 
        TYPE_WARNING, 
        TYPE_ERROR 
    } Type; 

    void Print(const char* const log, const Type type, const Int32 line, const char* const file);
}

