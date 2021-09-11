#pragma once

#include <sead.h>

class AreaRumbleMgr {
    SEAD_SINGLETON_DISPOSER(AreaRumbleMgr)

public:
    void rumble(s32 intensity, s8, s8, s8);
};
