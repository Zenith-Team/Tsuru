#pragma once

#include "actor/physicsactor.h"
#include "states.h"

class MultiStateActor : public PhysicsActor {  // size: 0x17C8
    SEAD_RTTI_OVERRIDE(MultiStateActor, PhysicsActor)

public:
    MultiStateActor(const ActorBuildInfo* buildInfo);
    virtual ~MultiStateActor() { }

    virtual void doStateChange(StateBase* state) {
        states.changeState(state);
    }

    StateWrapperMulti<MultiStateActor> states;  // 17A0
};
