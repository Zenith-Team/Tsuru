#pragma once

#include "sead.h"

class AreaRumbleMgr {
    SEAD_SINGLETON_DISPOSER(AreaRumbleMgr)

public:
    // Rumbles the screen
    // @param intensity The intensity of the rumbling
    void rumble(s32 intensity, s8 = 3, s8 = 0, s8 = 0);
};
