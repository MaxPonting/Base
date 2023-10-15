#pragma once

#include "../log/log.h"
#include "../type/type.h"

namespace Base::File
{
    Int32 ReadText(const Char* const filePath, Char* const output, const UInt64 outputSize)
    {
        FILE* fileStream;
        fileStream = fopen(filePath, "r");

        if(!fileStream)
        {
            Log::Print("File failed to open", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }

        UInt64 count = 0;

        while(1)
        {
            if(count == outputSize) 
            {
                Log::Print("File is too big", Log::Type::Warning, __LINE__, __FILE__);
                return 0;
            }

            output[count] = fgetc(fileStream);
            count++;

            if(feof(fileStream))
            {
                break;
            }
        }

        output[count - 1] = '\0';

        fclose(fileStream);

        return 1;
    }

    Int32 ReadBinary(const Char* filePath, Char* const output, const UInt64 outputSize)
    {
        FILE* fileStream;
        fileStream = fopen(filePath, "r");

        if(!fileStream)
        {
            Log::Print("File failed to open", Log::Type::Error, __LINE__, __FILE__);
            return 0;
        }

        UInt64 count = fread(output, sizeof(Char) * outputSize, 1, fileStream);

        if(count != 0) 
        {
            Log::Print("File is too big", Log::Type::Warning, __LINE__, __FILE__);
            return 0;
        }

        fclose(fileStream);

        return 1;
    }
}