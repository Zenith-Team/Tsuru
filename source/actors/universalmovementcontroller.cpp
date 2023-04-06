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
    bool safeMode = this->eventID2 >> 0x4 & 0x1;

    for (Actor** actor = ActorMgr::instance()->actors.start.buffer; actor < ActorMgr::instance()->actors.end.buffer; actor++) {
        if (*actor && (*actor)->initialStateFlag == (this->eventID1 & 0xFF)) {
            if (safeMode) {
                u32 targetID = 0;
                u32 targetIDSearch = ((this->settings1 >> 0x1C & 0xF) << 8) | ((this->settings1 >> 0x18 & 0xF) << 4) | ((this->settings1 >> 0x14 & 0xF));

                if ((this->eventID2 & 0xF) == 0) {
                    targetID = Profile::spriteToProfileList[targetIDSearch];
                } else {
                    targetID = targetIDSearch;
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
        this->movementHandler.link(this->position, this->movementHandler.getMaskForMovementType(this->settings2 & 0xFF), this->movementID);
    }

    return 1;
}

u32 UniversalMovementController::onExecute() {
    if (this->target) {
        this->movementHandler.execute();
        this->position = this->movementHandler.position;
        this->target->position = this->movementHandler.position;
    } else {
        this->onCreate();
    }

    return 1;
}
