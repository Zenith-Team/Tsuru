#include "game/actor/stage/stageactor.h"
#include "log.h"
#include "game/actor/actormgr.h"
#include "game/eventmgr.h"

class ActorManipulator : public StageActor {
    SEAD_RTTI_OVERRIDE(ActorManipulator, StageActor);

public:
    ActorManipulator(const ActorBuildInfo* buildinfo);
    virtual ~ActorManipulator() { }

    u32 onCreate() override;
    u32 onExecute() override;

    u8 trigEvent;
    bool isDone;

    void updateActor();

    StageActor* target;
};

REGISTER_PROFILE(ActorManipulator, ProfileID::ActorManipulator);

ActorManipulator::ActorManipulator(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
    , target(nullptr)
{}

u32 ActorManipulator::onCreate() {
    this->trigEvent = (this->eventID1 & 0xFF) - 1; // nybbles 1-2
    this->isDone = false;
    
    for (Actor** actor = &ActorMgr::instance()->actors.start.front(); actor != ActorMgr::instance()->actors.end; actor++) {
        if (*actor && (*actor)->initialStateFlag == ((settings1 >> 0x10) & 0xFF)) { // nybbles 7-8
            u32 targetID = 0;
            u32 inputID = this->settings1 & 0xFFF; // nybbles 10-12
            
            if (((this->settings1 >> 0xC) & 0xF)) { // nybble 9
                targetID = Profile::spriteToProfileList[inputID];
            } else {
                targetID = inputID;
            }

            if ((*actor)->getProfileID() == targetID) {
                this->target = (StageActor*)*actor;
                break;
            }
        }
    }
    
    return this->onExecute();
}

u32 ActorManipulator::onExecute() {
    if (((settings1 >> 0x18) & 0xF)) { // nybble 6
        if (!EventMgr::instance()->isActive(trigEvent)) {
            this->isDone = false;
        } else if (!this->isDone) {
            updateActor();
            this->isDone = true;
        }
    } else {
        if (!this->isDone) {
            updateActor();
            this->isDone = true;
        }
    }

    return 1;
}

void ActorManipulator::updateActor() {
    // Deletion
    if (((this->settings1 >> 0x1C) & 0xF)) { // nybble 5
        target->isDeleted = true;
    }

    // Scaling
    if (((this->settings2 >> 0x1C) & 0xF)) { // nybble 13
        target->scale.set(((this->settings2 >> 0x18) & 0xF), ((this->settings2 >> 0x14) & 0xF), ((this->settings2 >> 0x10) & 0xF)); // nybbles 14-16
        // Someone please figure out how to scale the actor's hitbox here. I'd absolutely love it! Thanks!
    }

    // Visibility
    target->isVisible = !(eventID2 & 0xF); // nybble 4

    // Activity
    target->isActive = !((eventID2 >> 0x4) & 0xF); // nybble 3

    // Size Changing??? TODO: Figure out what this does.
    if (((this->settings2 >> 0xC) & 0xF) == 1) { // nybble 17
        target->size.set(((settings2 >> 0x8) & 0xF), ((settings2 >> 0x4) & 0xF)); // nybbles 18 and 19
    }
}