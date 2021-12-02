#pragma once

#include <agl/utl/iparameterobj.h>
#include <agl/utl/inamedobj.h>

namespace agl { namespace env {

// TODO: This class has a lot more to it

class EnvObj : public utl::IParameterObj, utl::INamedObj { // Size: 0x108
public:
    class Index;
    class MetaInfo { };

public:
    EnvObj();

    void* registClass(const sead::SafeString&, const sead::SafeStringBase&, EnvObj* (*)(sead::Heap*), agl::env::EnvObj::MetaInfo, u32);

    u32 _74;
    u16 _78;
    u16 _7A;
    u8 _7C[60]; // Inlined class which inherits agl::utl::ParameterBase
    u8 _7C[60]; // Same as above
    u8 _F4[14]; // Same as above but a different class
};

static_assert(sizeof(EnvObj) == 0x108, "agl::env::EnvObj size mismatch");

} }
