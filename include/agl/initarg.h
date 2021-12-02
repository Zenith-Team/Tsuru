#pragma once

#include "types.h"

namespace agl {

struct InitArg { // Size: 0x140
    struct SubStruct1 { // Size: 0x10C
        struct SubStruct2 { // Size: 0xC
            SubStruct2();   // TODO: This is inlined, I'll do it later

            u32 _0;         // 0   // Inited to SubStruct1->_C
            void* _4;       // 4   // Inited to 0x101A484C
            u32 _8;         // 8   // Inited to 0x100
        };

        SubStruct1();       // TODO: This is inlined, I'll do it later

        SubStruct2 _0;      // 0
        u8 _C[0x10C - 0xC]; // C   // Unknown values
    };

    sead::Heap* _0;                             // 0
    u32 privateResourceWorkHeapSize;            // 4
    sead::Heap* _8;                             // 8
    u32 privateResourceShaderCompileHeapSize;   // C
    u32 _10;                                    // 10
    u32 allocatableSize;                        // 14
    u32 _18;                                    // 18
    u32 _1C;                                    // 1C
    u32 _20;                                    // 20
    u32 _24;                                    // 24
    u32 _28;                                    // 28
    u32 _2C;                                    // 2C
    SubStruct1 _30;                             // 30
    u8 _13C;                                    // 13C
};

static_assert(sizeof(InitArg) == 0x140, "agl::InitArg size mismatch");

}
