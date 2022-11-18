#include "game/actor/stage/stageactor.h"
#include "game/sound/sound.h"
#include "game/eventmgr.h"

class SoundPlayer : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(SoundPlayer, StageActor);

public:
    SoundPlayer(const ActorBuildInfo* buildInfo);
    virtual ~SoundPlayer() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;

    bool played;
};

const Profile SoundPlayerProfile(&SoundPlayer::build, ProfileID::SoundPlayer);

SoundPlayer::SoundPlayer(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
{ }

Actor* SoundPlayer::build(const ActorBuildInfo* buildInfo) {
    return new SoundPlayer(buildInfo);
}

u32 SoundPlayer::onCreate() {
    return this->onExecute();
}

u32 SoundPlayer::onExecute() {
    if (!EventMgr::instance()->isActive((this->eventID2 & 0xF) - 1)) {
        this->played = false;
    } else if (!this->played) {
        playSound(static_cast<SoundEffects::IDs>((this->eventID1 << 4 | this->eventID2 >> 4) + 0x1000000), this->position);
        this->played = true;
    }

    return 1;
}
