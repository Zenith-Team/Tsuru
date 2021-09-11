#pragma once

#ifdef Cemu
#include <dynlibs/os/functions.h>
#define LOG(FMT, ARGS ...)  __os_snprintf(logMsg, sizeof(logMsg), FMT, ## ARGS); OSConsoleWrite(logMsg, sizeof(logMsg))
#else
#define LOG(FMT, ARGS ...)  ((void (*)(const char* format, ...))(*(unsigned int*)(DATA_ADDR - 4)))(FMT, ## ARGS)
#endif
