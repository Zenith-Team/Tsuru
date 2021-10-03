#include <game/actor/stage/stageactor.h>
#include <game/profile/profileid.h>
#include <game/eventmgr.h>
#include <game/effect/effect.h>
#include <game/sound.h>
#include <log.h>

class EffectSpawner : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(EffectSpawner, StageActor)

public:
    EffectSpawner(const ActorBuildInfo* buildInfo);
    virtual ~EffectSpawner() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;

    bool played;
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
    if (EventMgr::instance()->isActive(this->eventID2-1) && !this->played) {
        this->played = true;
        
        switch (this->initialStateFlag) {
            case 0: { // Logging mode
                LOG("Particle effect: %x", this->settings1);
                LOG("Sound effect: %s", *sfxArray[this->settings2]);

                break;
            }

            case 1: { // Particle effect mode
                Vec3f effectPos(this->position.x, this->position.y, 4500.0f);
                Effect::spawn(this->settings1, &effectPos);
            
                break;
            }

            case 2: { // Sound effect mode
                playSound(*sfxArray[this->settings2], Vec2f(this->position.x, this->position.y));
            
                break;
            }

            case 3: { // Hybrid mode
                Vec3f effectPos(this->position.x, this->position.y, 4500.0f);
                Effect::spawn(this->settings1, &effectPos);

                playSound(*sfxArray[this->settings2], Vec2f(this->position.x, this->position.y));
            
                break;
            }
        }

        return 2;
    }

    return 1;
}
