#pragma once

#include <sead.h>
#include <types.h>

namespace agl { namespace lyr {

class Layer : public sead::IDisposer {
public:
    Layer();
    virtual ~Layer();

    // ...

    u8 _10[0x41C - 0x10];
};

class DrawMethod : public sead::IDisposer {

public:
    sead::SafeString mName;
    u32 _18;
    u32 _1C;
    u32 _20;
    u32 _24;
    u8 mMethod[8];  //! This is a PTMF, please make it into one
    u32 _30;
    u32 _34;
    u32 _38;
    u32 _3C;
};

} }
