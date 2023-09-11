#include "file/file.h"
#include "log/log.h"

#include <stdio.h>

namespace Base::File
{
    Int32 Read(const char* const file_path, char* const output, const Int32 size)
    {
        FILE* file_stream;
        file_stream = fopen(file_path, "r");

        if(file_stream == 0)
        {
            Log::Print("File failed to open", Log::TYPE_ERROR, __LINE__, __FILE__);
            return 0;
        }

        Int32 count = 0;

        while(1)
        {
            if(count == size) 
            {
                Log::Print("File failed to open", Log::TYPE_ERROR, __LINE__, __FILE__);
                return 0;
            }

            output[count] = fgetc(file_stream);
            count++;

            if(feof(file_stream))
            {
                break;
            }
        }

        output[count - 1] = '\0';

        return 1;
    }
}