#include "log/log.h"

#include <stdio.h>

static char* types[3] = 
{
    "MESSAGE",
    "WARNING",
    "ERROR"
};

void log_print(const LogType log_type, const char* const module, const char* const log, const int line_number)
{
    printf("[%s][%s/%d][%s]\n", types[log_type], module, line_number, log);
}