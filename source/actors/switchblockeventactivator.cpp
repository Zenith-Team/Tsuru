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

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onExecute() override;
};

const Profile SwitchBlockEventActivatorProfile(&SwitchBlockEventActivator::build, ProfileID::SwitchBlockEventActivator);

SwitchBlockEventActivator::SwitchBlockEventActivator(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
{
    LOG("%d", this->eventID1 >> 0x4 & 0xFF);
}

Actor* SwitchBlockEventActivator::build(const ActorBuildInfo* buildInfo) {
    return new SwitchBlockEventActivator(buildInfo);
}

u32 SwitchBlockEventActivator::onExecute() {
    if (EventMgr::instance()->isActive(this->eventID1 >> 0x4 & 0xFF)) {
        return 2;
    }

    if (TsuruSaveMgr::sSaveData.switchBlockBlue[SaveMgr::instance()->saveData->header.lastSessionSaveSlot] == (this->eventID2 >> 0x4 & 0xF ? 1 : 0)) {
        EventMgr::instance()->set(this->eventID1 >> 0x4 & 0xFF, 0, true);
        LOG("setting event %d to true", this->eventID1 >> 0x4 & 0xFF);
    }

    return 1;
}
