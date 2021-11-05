#pragma once

#include "sead/idisposer.h"
#include "sead/list.h"

class PlayerLookTarget;

class PlayerLookTargetMgr {
    SEAD_SINGLETON_DISPOSER(PlayerLookTargetMgr)

public:
    PlayerLookTargetMgr();
    virtual ~PlayerLookTargetMgr();

    // Adds a look target to the list
    // @param target The target to be added
    void add(PlayerLookTarget* target);

    // Removes a look target from the list and destructs it via idisposer
    // @param target The target to be removed
    void del(PlayerLookTarget* target);

    sead::OffsetList<PlayerLookTarget> lookTargets;
};
