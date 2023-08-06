#pragma once

typedef enum LogType 
{ 
    LOG_TYPE_MESSAGE, 
    LOG_TYPE_WARNING, 
    LOG_TYPE_ERROR 
} 
LogType;

void log_print(const LogType log_type, const char* const module, const char* const log, const int line_number);