#pragma once

#include <types.h>

class CSPlayerMgr { // Size: 0x34
public:
    CSPlayerMgr();

    void spawnPlayer();

    static CSPlayerMgr* sInstance;

    u8 mUnk1[16];
    u8 _10; // class
    u8 _11; // class
    u32 mPlayerActorID;
    u8 unk2[28];
};
