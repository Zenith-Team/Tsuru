#pragma once

#include "types.h"

namespace agl { namespace utl {

class ParameterBase;

class IParameterObj { // Size: 0x70
public:
    struct SubStruct1 { // Size: 0x10
        u32 _0;
        u32 _4;
        u32 _8;
        u32 _C;
    };

    struct SubStruct2 { // Size: 0x4C
        struct SubStruct {
            u32 _0;
            void* _4;
            u32 _8;
        };

        SubStruct _0;
        u8 _C[0x3F];    // Unknown values
        u8 _4B;
    };

public:
    IParameterObj();

    //! Temporarily here just to force the compiler to generate a vtable pointer
    virtual void forceVtablePtr() { }

    void pushBackListNode(agl::utl::ParameterBase*);

    SubStruct1 _0;
    SubStruct2 _10;
    u32 _5C;
    s32 _60;
    u32 _64;
    u32 _68;
};

} }
