#pragma once

#include "types.h"

class AreaTask
{
public:
    void readHaxxOptions();

    u8 _0[0x72C];
    u32 wrapFlag;
    u8 _730[0x4B4];

    static AreaTask* instance;
};
