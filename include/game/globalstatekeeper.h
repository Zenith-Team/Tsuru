#pragma once

#include "heap/seadDisposer.h"

ENUM_CLASS(LevelExitMethod,
    Quit = 1,
    Win = 2,
    Die = 3
);

class GlobalStateKeeper { // Size: 0x21E18 
    SEAD_SINGLETON_DISPOSER(GlobalStateKeeper);

public:
    GlobalStateKeeper();

    u8 _10[0x20-0x10];
    LevelExitMethod::__type__ levelExitMethod;
    u8 _24[0x1A8-0x24];
    u32 _1A8;
    u8 _1AC[0x1B8-0x1AC];
    u32 _1B8;
    u8 _1BC[0x21E18-0x1BC];
};

static_assert(sizeof(GlobalStateKeeper) == 0x21E18, "GlobalStateKeeper size mismatch");
