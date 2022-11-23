#include "game/actor/stage/stageactor.h"
#include "game/eventmgr.h"
#include "game/savemgr.h"
#include "tsuru/save/managers/tsurusavemgr.h"
#include "log.h"

class SwitchBlockEventActivator : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(SwitchBlockEventActivator, StageActor);

public:
    SwitchBlockEventActivator(const ActorBuildInfo* buildInfo);
    virtual ~SwitchBlockEventActivator() { }

    u32 onExecute() override;
};

REGISTER_PROFILE(SwitchBlockEventActivator, ProfileID::SwitchBlockEventActivator);

SwitchBlockEventActivator::SwitchBlockEventActivator(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
{
    PRINT(this->eventID1 >> 0x4 & 0xFF);
}

u32 SwitchBlockEventActivator::onExecute() {
    if (EventMgr::instance()->isActive(this->eventID1 >> 0x4 & 0xFF)) {
        return 2;
    }

    if (TsuruSaveMgr::sSaveData.switchBlockBlue[SaveMgr::instance()->saveData->header.lastSessionSaveSlot] == (this->eventID2 >> 0x4 & 0xF ? 1 : 0)) {
        EventMgr::instance()->set(this->eventID1 >> 0x4 & 0xFF, 0, true);
        PRINT("setting event ", this->eventID1 >> 0x4 & 0xFF, " to true");
    }

    return 1;
}
