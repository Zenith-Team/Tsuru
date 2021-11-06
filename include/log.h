#pragma once

#ifdef Cemu
#include <dynlibs/os/functions.h>
#define LOG(FMT, ...)  { __os_snprintf(logMsg, sizeof(logMsg), FMT, ## __VA_ARGS__); OSConsoleWrite(logMsg, sizeof(logMsg)); } (void)0
#else
#define LOG(FMT, ...) { ((void (*)(const char* format, ...))(*(unsigned int*)(DATA_ADDR - 4)))(FMT, ## __VA_ARGS__); } (void)0
#endif
