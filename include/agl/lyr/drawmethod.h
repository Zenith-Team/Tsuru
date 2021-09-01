#pragma once

#include <sead.h>
#include <types.h>

namespace agl { namespace lyr {

struct RenderInfo;

class DrawMethod : public sead::IDisposer {
public:
    typedef void (sead::TaskBase::*PTMF)(const RenderInfo& renderInfo); //? This is a hack, how does AGL handle this PTMF officially?

public:
    sead::SafeString name;
    u32 _18;
    u32 _1C;
    u32 _20;
    sead::TaskBase* _24;    //? Is this official?
    PTMF method;
    u32 _30;
    u32 _34;
    u32 _38;
    u32 _3C;
};

} }
