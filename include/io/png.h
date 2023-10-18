#pragma once

#include "../type/type.h"
#include "../memory/helper.h"
#include "../io/file.h"
#include "../allocator/allocator.h"

#include <stdio.h>

namespace Base::IO::PNG
{
    struct PNGChunk
    {
        Int32 dataLength;
        Byte type[4];
        Byte* data;
        Int32 crc32;
    };

    Int32 Read(const Char* const filePath, Char* const output, const UInt64 outputSize)
    {
        Char* data = 0;

        {
            UInt64 size = File::GetSize(filePath);
            data = (Char*)Allocator::Allocate(size);
            if(data == 0)
            {
                return 0;
            } 

            File::Read(filePath, data, size, true, false);
        }

        for(Int32 i = 0; i < 8; i++)
        {
            printf("%x ", data[i]);
        }

        return 1;
    }
}