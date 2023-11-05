#pragma once

#include "../log/log.h"
#include "../type/type.h"

#include <stdio.h>

namespace Base::IO::File
{
    UInt64 GetSize(const Char* const filePath)
    {
        FILE* fileStream;
        fileStream = fopen(filePath, "rb");

        if(!fileStream)
        {
            Log::Print("File '%s' failed to open", Log::Type::Error, __LINE__, __FILE__, filePath);
            return 0;
        }

        fseeko64(fileStream, 0, SEEK_END);

#if PLATFORM == PLATFORM_WINDOWS
        UInt64 size = _ftelli64(fileStream);
#elif PLATFORM == PLATFORM_LINUX || PLATFORM_MAC
        UInt64 size = ftello64(fileStream);
#endif

        fclose(fileStream);

        return size;
    }

    Int32 Read(const Char* const filePath, Char* const output, const UInt64 outputSize, const Bool binary, const Bool nullTerminate)
    {
        FILE* fileStream;
        fileStream = fopen(filePath, binary ? "rb" : "r");

        if(!fileStream)
        {
            Log::Print("File '%s' failed to open", Log::Type::Error, __LINE__, __FILE__, filePath);
            return 0;
        }

        fseeko64(fileStream, 0, SEEK_END);

#if PLATFORM == PLATFORM_WINDOWS
        UInt64 size = _ftelli64(fileStream);
#elif PLATFORM == PLATFORM_LINUX || PLATFORM_MAC
        UInt64 size = ftello64(fileStream);
#endif

        if(size > outputSize)
        {
            Log::Print("File %s is too big, it is %u bytes", Log::Type::Error, __LINE__, __FILE__, filePath, size);
            return 0;
        }

        fseek(fileStream, 0, SEEK_SET);

        UInt64 count = fread(output, sizeof(Char), outputSize, fileStream);

        if(nullTerminate)
        {
            if(outputSize == count)
            {
                Log::Print("No space for null termination after file '%s'", Log::Type::Error, __LINE__, __FILE__, filePath);
                return 0;
            }

            output[count] = '\0';
        }

        fclose(fileStream);

        return 1;
    }
}