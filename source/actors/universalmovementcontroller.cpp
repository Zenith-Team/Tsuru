#include "game/actor/stage/stageactor.h"
#include "game/movementhandler.h"
#include "game/actor/actormgr.h"
#include "log.h"

class UniversalMovementController : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(UniversalMovementController, StageActor);

public:
    UniversalMovementController(const ActorBuildInfo* buildInfo);
    virtual ~UniversalMovementController() { }

    u32 onCreate() override;
    u32 onExecute() override;

    StageActor* target;
    MovementHandler movementHandler;
};

REGISTER_PROFILE(UniversalMovementController, ProfileID::UniversalMovementController);

UniversalMovementController::UniversalMovementController(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
    , target(nullptr)
    , movementHandler()
{ }


u32 UniversalMovementController::onCreate() {
    bool safeMode = this->eventID2 >> 0x4 & 0x1; // nybble 3

    for (Actor** actor = ActorMgr::instance()->actors.start.buffer; actor < ActorMgr::instance()->actors.end.buffer; actor++) {
        if (*actor && (*actor)->initialStateFlag == (this->eventID1 & 0xFF)) { // nybbles 1-2
            if (safeMode) {
                u32 targetID = 0;
                u32 targetIDSearch = ((this->settings1 >> 0x1C & 0xF) << 8) | ((this->settings1 >> 0x18 & 0xF) << 4) | ((this->settings1 >> 0x14 & 0xF)); // nybbles 5-7
                if ((this->eventID2 & 0xF) == 0) { // nybble 4
                    targetID = Profile::spriteToProfileList[targetIDSearch]; // use profile id
                } else {
                    targetID = targetIDSearch; // use sprite id
                }

                if ((*actor)->getProfileID() == targetID) {
                    this->target = (StageActor*)*actor;
                    break;
                }
            } else {
                this->target = (StageActor*)*actor;
                break;
            }
        }
    }

    if (!this->target) {
        PRINT("Unable to find target for universal movement controller with id: ", this->eventID1 & 0xFF, ", trying again...");
    } else {
        this->movementHandler.link(this->target->position, this->movementHandler.getMaskForMovementType(this->settings2 & 0xFF), this->movementID);
    }

    return 1;
}

u32 UniversalMovementController::onExecute() {
    if (this->target) {
        this->movementHandler.execute();
        this->target->position = this->movementHandler.position;
    } else {
        this->onCreate();
    }

    return 1;
}
