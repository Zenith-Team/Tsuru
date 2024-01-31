#pragma once

#include "heap/seadDisposer.h"
#include "game/actor/courseselect/csplayerbase.h"

class CSPlayerMgr { // Size: 0x34
    SEAD_SINGLETON_DISPOSER(CSPlayerMgr);

public:
    CSPlayerMgr();

    void spawnPlayer();

    // @return Pointer to CS player actor
    CSPlayerBase* getPlayer();

    u8 _10;            // class
    u8 _11;            // class
    u32 playerActorID; // 12
    u8 _16[28];
};
