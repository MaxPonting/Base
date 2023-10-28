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
        UInt32 dataLength;
        Byte type[4];
        Byte* data;
        UInt32 crc32;
    };

    static PNGChunk ReadChunk(const Byte* const memory)
    {
        PNGChunk chunk = {0};
        chunk.dataLength = Memory::GetBigEndian32(memory);

        *((UInt32*)chunk.type) = *((UInt32*)(memory + 4));

        chunk.data = (Byte*)Allocator::Allocate(chunk.dataLength);

        memcpy(chunk.data, memory + 8, chunk.dataLength);

        chunk.crc32 = Memory::GetBigEndian32(memory + 8 + chunk.dataLength);

        return chunk;
    }

    struct ZLibBlock
    {
        Byte cmf;
        Byte extraFlags;
        Byte* data;
        UInt16 checkValue;
    };

    static ZLibBlock ReadZLibBlock(const Byte* const memory, const UInt32 length)
    {
        ZLibBlock block = {0};
        block.cmf = *memory;
        block.extraFlags = *(memory + 1);

        block.data = (Byte*)Allocator::Allocate(length - 4);

        memcpy(block.data, memory + 2, length - 4);

        block.checkValue = Memory::GetBigEndian16(memory + length - 2);

        return block;
    }

    Int32 Read(const Char* const filePath, Char* const output, const UInt64 outputSize)
    {
        Char* data = 0;
        UInt64 size = File::GetSize(filePath);

        data = (Char*)Allocator::Allocate(size);
        if(data == 0)
        {
            Log::Print("Allocator failed\n", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        } 

        File::Read(filePath, data, size, true, false);

        {
            Byte signature[8] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};

            if(memcmp(data, signature, 8) != 0)
            {
                Log::Print("File '%s' has invalid signature", Log::Type::Warning, __LINE__, __FILE__, filePath);
                return 0;
            }
        }

        Allocator::Deallocate(size);

        return 1;
    }
}