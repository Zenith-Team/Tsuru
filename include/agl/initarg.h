#pragma once

#include <types.h>

namespace agl {

struct InitArg { // Size: 0x140
    struct SubStruct1 { // Size: 0x10C
        struct SubStruct2 { // Size: 0xC
            SubStruct2();   // TODO: This is inlined, I'll do it later

            u32 _0;         // _0   // Inited to SubStruct1->_C
            void* _4;       // _4   // Inited to 0x101a484c
            u32 _8;         // _8   // Inited to 0x100
        };

        SubStruct1();       // TODO: This is inlined, I'll do it later

        SubStruct2 _0;      // _0
        u8 _C[0x10C - 0xC]; // _C   // Unknown values
    };

    u32 _0;                 // _0
    u32 _4;                 // _4
    u32 _8;                 // _8
    u32 _C;                 // _C
    u32 _10;                // _10
    u32 _14;                // _14
    u32 _18;                // _18
    u32 _1C;                // _1C
    u32 _20;                // _20
    u32 _24;                // _24
    u32 _28;                // _28
    u32 _2C;                // _2C
    SubStruct1 _30;         // _30
    u8 _13C;                // _13C
};

static_assert(sizeof(InitArg) == 0x140, "agl::InitArg size mismatch");

}
