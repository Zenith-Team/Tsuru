#pragma once

#include "game/actor/stage/stageactor.h"
#include "game/eventmgr.h"

extern f32 PlayerJumpArc;
extern f32 MiniPlayerJumpArc;
extern f32 PlayerJumpMax;
extern f32 PlayerDescentRate;

class PhysicsModifier : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(PhysicsModifier, StageActor)

public:
    PhysicsModifier(const ActorBuildInfo* buildInfo);
    virtual ~PhysicsModifier() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onExecute() override;
    bool activated;
};

const Profile PhysicsModifierProfile(&PhysicsModifier::build, ProfileID::PhysicsModifier);

PhysicsModifier::PhysicsModifier(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
{ }

Actor* PhysicsModifier::build(const ActorBuildInfo* buildInfo) {
    return new PhysicsModifier(buildInfo);
}

u32 PhysicsModifier::onExecute() {
    if (!this->activated && EventMgr::instance()->isActive(this->eventID2)) {
        PlayerJumpArc = 0.5f;
        MiniPlayerJumpArc = 0.5f;
        PlayerJumpMax = 4.5f;
        PlayerDescentRate = -2.0f;
        this->activated = true;
    }

    return 1;
}
