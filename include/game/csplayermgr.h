#pragma once

#include <sead.h>

class CSPlayerMgr { // Size: 0x34
    SEAD_SINGLETON_DISPOSER(CSPlayerMgr)

public:
    CSPlayerMgr();

    void spawnPlayer();

    u8 unk1[16];
    u8 _10; // class
    u8 _11; // class
    u32 mPlayerActorID;
    u8 unk2[28];
};
