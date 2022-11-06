#pragma once

#include "sead/random.h"
#include "game/actor/stage/player.h"

class PlayerMgr {
    SEAD_SINGLETON_DISPOSER(PlayerMgr);

public:
    inline Player* getRandomPlayer() {
        Player* out = nullptr;

        do {
            out = this->players[sead::randU32(4)];
        } while (!out);

        return out;
    }

    u32 _10;
    u32 _14;
    u32 _18;
    u32 _1C;
    Player* players[4];
    Player** ptrToPlayers;
    u32 _34;
    u32 _38;
    u32 _3C;
    u16 _40;
    u16 playerFlags;
    u32 _44;
    u32 _48;
    u32 _4C;
    u32 _50;
};
