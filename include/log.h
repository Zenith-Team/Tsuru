#pragma once

#ifdef Cemu
#include <dynlibs/os/functions.h>
#define LOG(FMT, ARGS...)  __os_snprintf(log_msg, sizeof(log_msg), FMT, ## ARGS);  \
                           OSConsoleWrite(log_msg, sizeof(log_msg))
#else
#define LOG(FMT, ARGS...)  ((void (*)(const char *format, ...))(*(unsigned int *)(DATA_ADDR - 4)))(FMT, ## ARGS)
#endif
