#pragma once

#include <types.h>
#include <sead.h>

class CSPlayerMgr { // Size: 0x34
    SEAD_SINGLETON_DISPOSER(CSPlayerMgr)

public:
    CSPlayerMgr();

    void spawnPlayer();

    u8 unk1[16];
    u8 _10; //? Is class
    u8 _11; //? Is class
    u32 playerActorID;
    u8 unk2[28];
};
