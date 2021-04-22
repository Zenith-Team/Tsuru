#include "actor/actor.h"
#include "eventmgr.h"
#include "effect.h"
#include "movementhandler.h"
#include "sound.h"


class EffectSpawner : public Actor {
    SEAD_RTTI_OVERRIDE_IMPL(EffectSpawner, Actor)

public:
    EffectSpawner(const ActorBuildInfo* buildInfo);
    virtual ~EffectSpawner() { }

    static BaseActor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;

    EffectWrapper effect;
    s32 effectId;
    MovementHandler movementHandler;

    bool spawned;

    bool spawnEffect;
    bool nonUpdatedEffect;
    u32 effectLength;
    u32 effectTimer;

    bool playSoundEffect;
    u32 soundId;

    static const f32 effectScales[16];
};

const Profile EffectSpawnerProfile(&EffectSpawner::build, ProfileId::Sprite134, "EffectSpawner", nullptr, 0);

const f32 EffectSpawner::effectScales[16] = { 1.0f, 0.1f, 0.25f, 0.5f, 0.75f, 0.875f, 1.125f, 1.25f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 5.0f, 6.0f };



EffectSpawner::EffectSpawner(const ActorBuildInfo* buildInfo)
    : Actor(buildInfo)
    , effect()
    , effectId(-1)
    , movementHandler()
    , spawned(false)
    , spawnEffect(false)
    , nonUpdatedEffect(false)
    , effectLength(0)
    , effectTimer(0)
    , playSoundEffect(false)
    , soundId(0)
{ }

BaseActor* EffectSpawner::build(const ActorBuildInfo* buildInfo) {
    return new EffectSpawner(buildInfo);
}


u32 EffectSpawner::onCreate() {
    if (!eventId2)
        return 2;

    if (settings2 & 0xF0)
        scale.set(effectScales[(settings2 >> 4) & 0xF]);

    u32 movementMask = movementHandler.getMaskForMovementType(settings2 & 0xF);
    movementHandler.link(position, movementMask, movementId);

    spawnEffect = !((settings1 >> 12) & 1);
    effectId = settings1 >> 20;
    nonUpdatedEffect = (settings1 >> 16) & 1;
    effectLength = settings1 & 0xFFF;

    playSoundEffect = !((settings2 >> 16) & 1);
    soundId = (settings2 >> 20) + 0x01000000;

    return onExecute();
}

u32 EffectSpawner::onExecute() {
    movementHandler.execute();
    position = movementHandler.position;

    if (EventMgr::instance->isActive(eventId2 - 1)) {
        if (!spawned) {
            effectTimer = 0;

            if (spawnEffect && nonUpdatedEffect)
                Effect::spawn(effectId, &position, &rotation, &scale);
            else
                effectTimer = 0;

            if (playSoundEffect) {
                const char* soundLabel = SoundSystem::sInstance->GetItemLabel(soundId);
                if (soundLabel)
                    PlaySound(soundLabel, position);
            }

            spawned = true;
        }

        if (spawnEffect && !nonUpdatedEffect) {
            if (!effectLength || effectTimer < effectLength)
                effect.update(effectId, &position, &rotation, &scale);
            else
                effect.update(-1, &position, &rotation, &scale);

            if (effectLength)
                effectTimer++;
        }
    }
    else {
        if (spawnEffect)
            effect.update(-1, &position, &rotation, &scale);

        spawned = false;
    }

    return 1;
}
