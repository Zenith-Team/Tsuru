#include <game/actor/stage/stageactor.h>
#include <game/profile/profileid.h>
#include <game/eventmgr.h>
#include <game/effect/effect.h>
#include <log.h>

class EffectSpawner : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(EffectSpawner, StageActor)

public:
    EffectSpawner(const ActorBuildInfo* buildInfo);
    virtual ~EffectSpawner() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
};

const Profile EffectSpawnerProfile(&EffectSpawner::build, ProfileID::EffectSpawner, "EffectSpawner", nullptr, 0);

EffectSpawner::EffectSpawner(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
{ }

Actor* EffectSpawner::build(const ActorBuildInfo* buildInfo) {
    return new EffectSpawner(buildInfo);
}

u32 EffectSpawner::onCreate() {
    if (!this->eventID2)
        return 2;

    return this->onExecute();
}

u32 EffectSpawner::onExecute() {
    if (EventMgr::instance()->isActive(this->eventID2-1)) {
        LOG("fx %x", this->settings1);
        Vec3f effectPos(this->position.x, this->position.y, 4500.0f);
        Effect::spawn(this->settings1, &effectPos);
        return 2;
    }

    return 1;
}
