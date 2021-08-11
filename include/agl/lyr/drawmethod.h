#pragma once

#include <sead.h>
#include <types.h>

namespace agl { namespace lyr {

class DrawMethod : public sead::IDisposer {
    typedef void (DrawMethod::*PTMF)();

public:
    sead::SafeString mName;
    u32 _18;
    u32 _1C;
    u32 _20;
    u32 _24;
    PTMF mMethod;
    u32 _30;
    u32 _34;
    u32 _38;
    u32 _3C;
};

} }
