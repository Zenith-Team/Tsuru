#include "game/eventmgr.h"
#include "game/playermgr.h"
#include "game/actor/stage/stageactor.h"
#include "game/actor/stage/player.h"

class PowerupSwitcher : public StageActor {
    SEAD_RTTI_OVERRIDE(PowerupSwitcher, StageActor);

public:
    PowerupSwitcher(const ActorBuildInfo* buildInfo);
    virtual ~PowerupSwitcher() { }

    u32 onExecute() override;
};

REGISTER_PROFILE(PowerupSwitcher, ProfileID::PowerupSwitcher);

PowerupSwitcher::PowerupSwitcher(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
{ }

u32 PowerupSwitcher::onExecute() {
    if (EventMgr::instance()->isActive((this->eventID1 >> 0x4 & 0xF) - 1)) {
        for (u32 i = 0; i < 4; i++) {
            if (PlayerMgr::instance()->players[i]) {
                PlayerMgr::instance()->players[i]->givePowerup(static_cast<PlayerBase::PowerupState::__type__>(this->eventID1 & 0xF));
                this->isDeleted = true;
            }
        }
    }

    return 1;
}
