#pragma once

#include "actor/player.h"
#include "sead.h"


class PlayerMgr : public sead::IDisposer {  // size: 0x54
public:
    static PlayerMgr* instance;

    u32 _10;                // 10
    u32 _14;                // 14
    u32 _18;                // 18
    u32 _1C;                // 1C
    Player* players[4];     // 20
    Player** ptrToPlayers;  // 30
    u32 _34;                // 34
    u32 _38;                // 38
    u32 _3C;                // 3C
    u16 _40;                // 40
    u16 playerFlags;        // 42
    u32 _44;                // 44
    u32 _48;                // 48
    u32 _4C;                // 4C
    u32 _50;                // 50
};
