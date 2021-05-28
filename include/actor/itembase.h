#pragma once

#include "multistateactor.h"

class ItemBase : public MultiStateActor {
    SEAD_RTTI_OVERRIDE(ItemBase, MultiStateActor);

public:
    ItemBase(const ActorBuildInfo* buildInfo);
    virtual ~ItemBase();

    // TODO
};
