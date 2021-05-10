#pragma once

#include "types.h"

class AreaTask {  // size: 0xBE4
public:
    void readOptions();

    u8 _0[0x72C];     // 0
    u32 wrapFlag;     // 72C
    u8 _730[0x4B4];   // 730

    static AreaTask* instance;
};
