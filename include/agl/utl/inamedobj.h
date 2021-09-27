#pragma once

#include <types.h>

namespace agl { namespace utl {

class INamedObj { // Size: 0x4
public:
    virtual ~INamedObj();

    // TODO: More virtual functions here
};

static_assert(sizeof(INamedObj) == 0x4, "agl::utl::INamedObj size mismatch");

} }
