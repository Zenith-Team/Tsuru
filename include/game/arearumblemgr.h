#pragma once

#include "sead.h"

class ZoneRumbleMgr {
    SEAD_SINGLETON_DISPOSER(ZoneRumbleMgr)

public:
    void rumble(s32 intensity, s8 = 3, s8 = 0, s8 = 0);
};
