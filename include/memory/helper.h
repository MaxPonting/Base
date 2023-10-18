#pragma once

#include "../type/type.h"

namespace Base::Memory
{
    UInt64 GetBigEndian64(const Byte* const memory)
    {
        UInt64 result = 0;
        for(UInt64 i = 0; i < 8; i++)
        {
            result <<= 8;
            result |= *(memory + i);
        }

        return result;
    }
 
    UInt32 GetBigEndian32(const Byte* const memory)
    {
        UInt32 result = 0;
        for(UInt32 i = 0; i < 4; i++)
        {
            result <<= 8;
            result |= *(memory + i);
        }

        return result;
    }

    UInt16 GetBigEndian16(const Byte* const memory)
    {
        UInt16 result = 0;
        for(UInt16 i = 0; i < 2; i++)
        {
            result <<= 8;
            result |= *(memory + i);
        }

        return result;
    }
}