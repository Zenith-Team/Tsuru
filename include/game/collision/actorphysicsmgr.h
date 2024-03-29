#pragma once

#include "game/collision/physicsmgr.h"

class ActorPhysicsMgr : public PhysicsMgr {
    SEAD_RTTI_OVERRIDE_DECL(ActorPhysicsMgr, PhysicsMgr);

public:
    ActorPhysicsMgr();

    virtual u32 vf3C();
    virtual u32 vf44();
    virtual u32 vf4C();
};
