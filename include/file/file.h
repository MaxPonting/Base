#pragma once

#include "../type/type.h"

namespace Base::File
{
    Int32 Read(const char* const file_path, char* const output, const Int32 size);
}