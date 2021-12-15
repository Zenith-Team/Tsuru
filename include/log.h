#pragma once

#include "sead/graphicscontext.h"

#ifdef Cemu
#include "dynlibs/os/functions.h"
#define LOG(FMT, ...) { \
    __os_snprintf(logMsg, sizeof(logMsg), FMT, ## __VA_ARGS__); \
    __os_snprintf(logMsg, sizeof(logMsg), "%s%s", logMsg, LogColor::Reset); \
    OSConsoleWrite(logMsg, sizeof(logMsg)); } (void)0
#else
#define LOG(FMT, ...) \
    { ((void (*)(const char* format, ...))(*(unsigned int*)(DATA_ADDR - 4)))(FMT, ## __VA_ARGS__); } (void)0
#endif

/* Logging Colors */
namespace LogColor {
#ifdef Cemu
    static const char* Reset        = "\33[0m";
    static const char* Bold         = "\33[1m";
    static const char* NoBold       = "\33[22m";
    static const char* Underline    = "\33[4m";
    static const char* NoUnderline  = "\33[24m";
    static const char* Invert       = "\33[7m";
    static const char* NoInvert     = "\33[27m";

    static const char* Black        = "\33[30m";
    static const char* Red          = "\33[31m";
    static const char* Green        = "\33[32m";
    static const char* Yellow       = "\33[33m";
    static const char* Blue         = "\33[34m";
    static const char* Magenta      = "\33[35m";
    static const char* Cyan         = "\33[36m";
    static const char* LightGray    = "\33[37m";
    static const char* Gray         = "\33[90m";
    static const char* LightRed     = "\33[91m";
    static const char* LightGreen   = "\33[92m";
    static const char* LightYellow  = "\33[93m";
    static const char* LightBlue    = "\33[94m";
    static const char* LightMagenta = "\33[95m";
    static const char* LightCyan    = "\33[96m";
    static const char* White        = "\33[97m";
    static const char* Default      = "\33[39m";
    //static const char* Extended     = "\33[38m";
    
    namespace BG {
        static const char* Black        = "\33[40m";
        static const char* Red          = "\33[41m";
        static const char* Green        = "\33[42m";
        static const char* Yellow       = "\33[43m";
        static const char* Blue         = "\33[44m";
        static const char* Magenta      = "\33[45m";
        static const char* Cyan         = "\33[46m";
        static const char* LightGray    = "\33[47m";
        static const char* Gray         = "\33[100m";
        static const char* LightRed     = "\33[101m";
        static const char* LightGreen   = "\33[102m";
        static const char* LightYellow  = "\33[103m";
        static const char* LightBlue    = "\33[104m";
        static const char* LightMagenta = "\33[105m";
        static const char* LightCyan    = "\33[106m";
        static const char* White        = "\33[107m";
        static const char* Default      = "\33[49m";
        //static const char* Extended     = "\33[48m";
    }
#else
    static const char* Reset        = "";
    static const char* Bold         = "";
    static const char* NoBold       = "";
    static const char* Underline    = "";
    static const char* NoUnderline  = "";
    static const char* Invert       = "";
    static const char* NoInvert     = "";

    static const char* Black        = "";
    static const char* Red          = "";
    static const char* Green        = "";
    static const char* Yellow       = "";
    static const char* Blue         = "";
    static const char* Magenta      = "";
    static const char* Cyan         = "";
    static const char* LightGray    = "";
    static const char* Gray         = "";
    static const char* LightRed     = "";
    static const char* LightGreen   = "";
    static const char* LightYellow  = "";
    static const char* LightBlue    = "";
    static const char* LightMagenta = "";
    static const char* LightCyan    = "";
    static const char* White        = "";
    static const char* Default      = "";
    //static const char* Extended     = "";
    
    namespace BG {
        static const char* Black        = "";
        static const char* Red          = "";
        static const char* Green        = "";
        static const char* Yellow       = "";
        static const char* Blue         = "";
        static const char* Magenta      = "";
        static const char* Cyan         = "";
        static const char* LightGray    = "";
        static const char* Gray         = "";
        static const char* LightRed     = "";
        static const char* LightGreen   = "";
        static const char* LightYellow  = "";
        static const char* LightBlue    = "";
        static const char* LightMagenta = "";
        static const char* LightCyan    = "";
        static const char* White        = "";
        static const char* Default      = "";
        //static const char* Extended     = "";
    }
#endif
};

/* Specialized logging functions */

void LogGraphicsContext(volatile sead::GraphicsContext& gc);
