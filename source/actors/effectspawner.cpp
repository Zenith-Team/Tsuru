#include "game/actor/stage/stageactor.h"
#include "game/effect/effect.h"
#include "game/eventmgr.h"

class EffectSpawner : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(EffectSpawner, StageActor);

public:
    EffectSpawner(const ActorBuildInfo* buildInfo);
    virtual ~EffectSpawner() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;

    bool spawned;
};

const Profile EffectSpawnerProfile(&EffectSpawner::build, ProfileID::EffectSpawner);

EffectSpawner::EffectSpawner(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
{ }

Actor* EffectSpawner::build(const ActorBuildInfo* buildInfo) {
    return new EffectSpawner(buildInfo);
}

u32 EffectSpawner::onCreate() {
    return this->onExecute();
}

u32 EffectSpawner::onExecute() {
    if (!EventMgr::instance()->isActive((this->eventID2 & 0xF) - 1)) {
        this->spawned = false;
    } else if (!this->spawned) {
        Effect::spawn(this->eventID1 << 4 | this->eventID2 >> 4, &this->position, &this->rotation, &this->scale);
        this->spawned = true;
    }

    return 1;
}
