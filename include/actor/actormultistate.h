#pragma once

#include "stageactor.h"
#include "states.h"

class ActorMultiState : public StageActor {  // size: 0x17C8
    SEAD_RTTI_OVERRIDE(ActorMultiState, StageActor)

public:
    ActorMultiState(const ActorBuildInfo* buildInfo);
    virtual ~ActorMultiState() { }

    virtual void doStateChange(StateBase* state) {
        states.changeState(state);
    }

    StateWrapperMulti<ActorMultiState> states;  // 17A0
};
