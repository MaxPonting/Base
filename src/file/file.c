#include "file/file.h"
#include "allocator/allocator.h"
#include "log/log.h"

#include <stdio.h>

int32 file_read(const char* const file_path, char* const output, const uint64 size)
{
    FILE* file_stream;
    file_stream = fopen(file_path, "r");

    if(file_stream == 0)
    {
        log_print(LOG_TYPE_ERROR, "BASE/FILE/FILE_PARSER", "File failed to open", __LINE__);
        return 0;
    }

    uint64 count = 0;

    while(1)
    {
        if(count == size) 
        {
            log_print(LOG_TYPE_ERROR, "BASE/FILE/FILE_PARSER", "File is larger than specified", __LINE__);
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