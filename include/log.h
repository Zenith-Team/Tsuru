#pragma once

#include "sead/graphicscontext.h"
#include "dynlibs/os/functions.h"
#include "tsuru/utils.h"
#include "game/collision/solid/polygoncollider.h"
#include <cstring>

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

namespace fmt {
    class _Hex {};

    extern _Hex hex;
    extern bool _hexActive;
}

template <typename T>
void tprint(T t);

#define PRINT_SINGLE(x) tprint(x);

#if defined(TSURU_DEBUG) && defined(NO_INTELLISENSE_HACK) && defined(Cemu)
    #define PRINT(...)                                                      \
        do {                                                                \
            PP_FOREACH(PRINT_SINGLE, __VA_ARGS__)                           \
            PRINT_SINGLE(LogColor::Reset)                                   \
            OSConsoleWrite(logMsg, sizeof(logMsg));                         \
            for (size_t i = 0; i < sizeof(logMsg); i++) { logMsg[i] = 0; }  \
        } while (0)

    #define LOG(FMT, ...) \
        {size_t len = strlen(logMsg); \
        __os_snprintf(logMsg + len, sizeof(logMsg) - len, FMT, __VA_ARGS__);}
#else
    #define PRINT(...) do {;} while (0)
    #define LOG(FMT, ...) do {;} while (0)
#endif

// Specializations

template <>
inline void tprint<fmt::_Hex>(fmt::_Hex) {
    LOG("%s", "0x");

    fmt::_hexActive = true;
}

template <>
inline void tprint<u8>(u8 value) {
    if (fmt::_hexActive) {
        fmt::_hexActive = false;
        LOG("%02X", value);
    } else {
        LOG("%u", value);
    }
}

template <>
inline void tprint<s8>(s8 value) {
    if (fmt::_hexActive) {
        fmt::_hexActive = false;
        LOG("%02X", value);
    } else {
        LOG("%d", value);
    }
}

template <>
inline void tprint<u16>(u16 value) {
    if (fmt::_hexActive) {
        fmt::_hexActive = false;
        LOG("%04X", value);
    } else {
        LOG("%u", value);
    }
}

template <>
inline void tprint<s16>(s16 value) {
    if (fmt::_hexActive) {
        fmt::_hexActive = false;
        LOG("%04X", value);
    } else {
        LOG("%d", value);
    }
}

template <>
inline void tprint<u32>(u32 value) {
    if (fmt::_hexActive) {
        fmt::_hexActive = false;
        LOG("%08X", value);
    } else {
        LOG("%u", value);
    }
}

template <>
inline void tprint<s32>(s32 value) {
    if (fmt::_hexActive) {
        fmt::_hexActive = false;
        LOG("%08X", value);
    } else {
        LOG("%d", value);
    }
}

template <>
inline void tprint<unsigned long>(unsigned long value) {
    if (fmt::_hexActive) {
        fmt::_hexActive = false;
        LOG("%08X", value);
    } else {
        LOG("%u", value);
    }
}

template <>
inline void tprint<long>(long value) {
    if (fmt::_hexActive) {
        fmt::_hexActive = false;
        LOG("%08X", value);
    } else {
        LOG("%d", value);
    }
}

template <>
inline void tprint<u64>(u64 value) {
    if (fmt::_hexActive) {
        fmt::_hexActive = false;
        LOG("%016llX", value);
    } else {
        LOG("%llu", value);
    }
}

template <>
inline void tprint<s64>(s64 value) {
    if (fmt::_hexActive) {
        fmt::_hexActive = false;
        LOG("%016llX", value);
    } else {
        LOG("%lld", value);
    }
}

template <>
inline void tprint<f32>(f32 value) {
    if (fmt::_hexActive) {
        fmt::_hexActive = false;
        LOG("%08X", *(u32*)&value);
    } else {
        LOG("%f", value);
    }
}

template <>
inline void tprint<f64>(f64 value) {
    if (fmt::_hexActive) {
        fmt::_hexActive = false;
        LOG("%016llX", *(u64*)&value);
    } else {
        LOG("%f", value);
    }
}

template <>
inline void tprint<bool>(bool value) {
    LOG("%s", formatBool(value));

    if (fmt::_hexActive) {
        fmt::_hexActive = false;
    }
}

template <>
inline void tprint<const char*>(const char* value) {
    LOG("%s", value);

    if (fmt::_hexActive) {
        fmt::_hexActive = false;
    }
}

template <>
inline void tprint<char*>(char* value) {
    LOG("%s", value);

    if (fmt::_hexActive) {
        fmt::_hexActive = false;
    }
}

template <>
inline void tprint<const char>(const char value) {
    LOG("%c", value);

    if (fmt::_hexActive) {
        fmt::_hexActive = false;
    }
}

template <>
inline void tprint<char>(char value) {
    LOG("%c", value);

    if (fmt::_hexActive) {
        fmt::_hexActive = false;
    }
}

template <>
inline void tprint<void*>(void* value) {
    if (fmt::_hexActive) {
        fmt::_hexActive = false;
        LOG("%p", value);
    } else {
        LOG("%p", value);
    }
}

template <>
inline void tprint<Vec2u>(Vec2u value) {
    LOG("X: %u, Y: %u", value.x, value.y);

    if (fmt::_hexActive) {
        fmt::_hexActive = false;
    }
}

template <>
inline void tprint<Vec3u>(Vec3u value) {
    LOG("X: %u, Y: %u, Z: %u", value.x, value.y, value.z);

    if (fmt::_hexActive) {
        fmt::_hexActive = false;
    }
}

template <>
inline void tprint<Vec2f>(Vec2f value) {
    LOG("X: %f, Y: %f", value.x, value.y);

    if (fmt::_hexActive) {
        fmt::_hexActive = false;
    }
}

template <>
inline void tprint<Vec3f>(Vec3f value) {
    LOG("X: %f, Y: %f, Z: %f", value.x, value.y, value.z);

    if (fmt::_hexActive) {
        fmt::_hexActive = false;
    }
}

template <>
inline void tprint<PolygonCollider::Info>(PolygonCollider::Info info) {
    LOG("\n------------------PolygonCollider::Info------------------\n", "");
    LOG("  offset: ", ""); tprint(info.offset); LOG("\n", "");
    LOG("  _8: %f\n", info._8);
    LOG("  _C: %f\n", info._C);
    LOG("  topLeft: ", ""); tprint(info.topLeft); LOG("\n", "");
    LOG("  bottomRight: ", ""); tprint(info.bottomRight); LOG("\n", "");
    LOG("  rotation: %u\n", info.rotation);
    LOG("--------------------------------------------------------", "");
}

template <>
inline void tprint<volatile sead::GraphicsContext&>(volatile sead::GraphicsContext& gc) {
    LOG("------------------GraphicsContext------------------", "");
    LOG("  alphaTest: Enable(%s), Func(%d), Ref(%f)", formatBool(gc.alphaTestEnable), gc.alphaTestFunc, gc.alphaTestRef);
    LOG("  blendConstantColor: RGBA(%f, %f, %f, %f)", gc.blendConstantColor.r, gc.blendConstantColor.g, gc.blendConstantColor.b, gc.blendConstantColor.a);
    LOG("  blendEnable:    %s", formatBool(gc.blendEnable));
    LOG("  blendEquation:  RGB(%d), A(%d)", gc.blendEquationRGB, gc.blendEquationA);
    LOG("  blendFactorDst: RGB(%d), A(%d)", gc.blendFactorDstRGB, gc.blendFactorDstA);
    LOG("  blendFactorSrc: RGB(%d), A(%d)", gc.blendFactorSrcRGB, gc.blendFactorSrcA);
    LOG("  colorMask: RGBA(%s, %s, %s, %s)", formatBool(gc.colorMaskR), formatBool(gc.colorMaskG), formatBool(gc.colorMaskB), formatBool(gc.colorMaskA));
    LOG("  cullingMode: %d", gc.cullingMode);
    LOG("  depthFunc:   %d", gc.depthFunc);
    LOG("  depth(Test/Write)Enable: %s / %s", formatBool(gc.depthTestEnable), formatBool(gc.depthWriteEnable));
    LOG("  renderStatePolygonMode: Back(%d), Front(%d)", gc.renderState.polygonModeBack, gc.renderState.polygonModeFront);
    LOG("  renderStatePolyOffset(Back/Front)Enable: %d / %d", gc.renderState.polyOffsetBackEnable, gc.renderState.polyOffsetFrontEnable);
    LOG("  renderStatePolyLineOffsetEnable: %d", gc.renderState.polyLineOffsetEnable);
    LOG("  stencilOp: Fail(%d), ZFail(%d), ZPass(%d)", gc.stencilOpFail, gc.stencilOpZFail, gc.stencilOpZPass);
    LOG("  stencilTest: Enable(%s), Func(%d), Mask(%d), Ref(%d)", formatBool(gc.stencilTestEnable), gc.stencilTestFunc, gc.stencilTestMask, gc.stencilTestRef);
    LOG("---------------------------------------------------", "");

    if (fmt::_hexActive) {
        fmt::_hexActive = false;
    }
}
