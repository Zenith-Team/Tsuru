#pragma once

#include "types.h"
#include "sead/safestring.h"

namespace agl { namespace utl {

class IParameterObj;

class ParameterBase { // Size: 0x10
public:
    ParameterBase();

    //! Temporarily here just to force the compiler to generate a vtable pointer
    virtual void forceVtablePtr() { }

    void calcHash(const sead::SafeString& hash);
    void initializeListNode(const sead::SafeString&, const sead::SafeString&, const sead::SafeString&, IParameterObj*);

    u32 _0;
    u32 _4;
    u32 _8;
};

static_assert(sizeof(ParameterBase) == 0x10, "agl::utl::ParameterBase size mismatch");

} }
