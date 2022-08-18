#include "log.h"
#include "game/eventmgr.h"
#include "game/playermgr.h"
#include "game/actor/stage/stageactor.h"


class PowerupSwitcher : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(PowerupSwitcher, StageActor)

public:
    PowerupSwitcher(const ActorBuildInfo* buildInfo);
    virtual ~PowerupSwitcher() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
};

const Profile PowerupSwitcherProfile(&PowerupSwitcher::build, ProfileID::PowerupSwitcher);

PowerupSwitcher::PowerupSwitcher(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
{ }

Actor* PowerupSwitcher::build(const ActorBuildInfo* buildInfo) {
    return new PowerupSwitcher(buildInfo);
}

u32 PowerupSwitcher::onCreate() {
    return this->onExecute();


}
u32 PowerupSwitcher::onExecute() {
    if (EventMgr::instance()->isActive((this->eventID1 >> 0x4 & 0xF) - 1)) {
        for (u32 i = 0; i < 4; i++) {
            if (PlayerMgr::instance()->players[i]) {
                PlayerMgr::instance()->players[i]->powerupState = static_cast<PlayerBase::PowerupState>(this->eventID1 & 0xF);
                this->isDeleted = true;
            }
        }
    }
    return 1;
}
