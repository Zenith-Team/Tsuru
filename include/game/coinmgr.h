#pragma once

#include "sead/idisposer.h"

class CoinMgr {
    SEAD_SINGLETON_DISPOSER(CoinMgr);

public:
    void spawnItemCoin(const Vec3f& position, u32 direction, u8 playerID);

    // TODO: members
};
