#pragma once

#include "actormultistate.h"

class ItemBase : public ActorMultiState {
    SEAD_RTTI_OVERRIDE(ItemBase, ActorMultiState);

public:
    ItemBase(const ActorBuildInfo* buildInfo);
    virtual ~ItemBase();

    // TODO
};
