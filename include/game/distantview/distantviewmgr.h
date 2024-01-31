#pragma once

#include "heap/seadDisposer.h"
#include "game/graphics/model/modelnw.h"

class DistantViewMgr
{
    SEAD_SINGLETON_DISPOSER(DistantViewMgr);

public:
    u8 _10[0x220 - 0x10];
    ModelWrapper* model;
    u8 _224[0x1460 - 0x224];
};
static_assert(sizeof(DistantViewMgr) == 0x1460);
