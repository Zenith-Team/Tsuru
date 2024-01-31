#pragma once

#include "heap/seadDisposer.h"

class CoinMgr {
    SEAD_SINGLETON_DISPOSER(CoinMgr);

public:
    void spawnItemCoin(const sead::Vector3f& position, u32 direction, u8 playerID);

    // TODO: members
};
