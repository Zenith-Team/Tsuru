#pragma once

#include "blockbase.h"

class CoinBase : public MovementBlockCoinBase {
    SEAD_RTTI_OVERRIDE(CoinBase, MovementBlockCoinBase)

public:
    CoinBase(const ActorBuildInfo* buildInfo);
    virtual ~CoinBase();

    // TODO
};
