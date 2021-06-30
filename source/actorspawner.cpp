#include "actor/stageactor.h"

#include "profile.h"
#include "actormgr.h"
#include "eventmgr.h"

class ActorSpawner : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(ActorSpawner, StageActor)

public:
    ActorSpawner(const ActorBuildInfo* buildInfo);
    virtual ~ActorSpawner() { }

    static BaseActor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;

    u16 spawnProfileId;
    bool spawned;
};

const Profile ActorSpawnerProfile(&ActorSpawner::build, Profile::spriteToProfileList[436], "ActorSpawner", nullptr, 0);
PROFILE_RESOURCES(Profile::spriteToProfileList[436]);



ActorSpawner::ActorSpawner(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
    , spawnProfileId(0)
    , spawned(false)
{ }

BaseActor* ActorSpawner::build(const ActorBuildInfo* buildInfo) {
    return new ActorSpawner(buildInfo);
}

u32 ActorSpawner::onCreate() {
    if (!eventId2)
        return 2;

    u16 inputId = linkId | ((movementId & 0xF) << 8);

    if (movementId & 0x10)
        spawnProfileId = Profile::Profile::spriteToProfileList[inputId];
    else
        spawnProfileId = inputId;

    return onExecute(); //Call onExecute() to prevent the spawned actor to be missing for one frame if the event is alredy active.
}

u32 ActorSpawner::onExecute() {
    BaseActor* child = (childList.begin() != childList.end()) ? childList.begin().mPtr : nullptr;

    if (EventMgr::instance->isActive(eventId2-1)) {
        if (initStateFlag == 2 && child) {
            StageActor* actor = sead::DynamicCast<StageActor, BaseActor>(child);

            if (actor) {
                actor->isActive = true;
                actor->isVisible = true;
                actor->addHitboxColliders();
            }

            return 1;
        }

        if (!spawned) {
            ActorBuildInfo buildInfo = { 0 };

            buildInfo.parentId = id;
            buildInfo.settings1 = settings1;
            buildInfo.settings2 = settings2;
            buildInfo.profile = Profile::get(spawnProfileId);
            buildInfo.position = position;
            buildInfo.eventId1 = eventId1 & 0xF;
            buildInfo.eventId2 = (eventId1 >> 4) & 0xF;

            ActorMgr::instance->create(&buildInfo, 0);

            spawned = true;
        }
    }
    else {
        if (initStateFlag == 1 && child) {
            child->isDeleted = true;
        }
        else if (initStateFlag == 2 && child) {
            StageActor* actor = sead::DynamicCast<StageActor, BaseActor>(child);

            if (actor) {
                actor->isActive = false;
                actor->isVisible = false;
                actor->removeHitboxColliders();
            }
        }

        spawned = false;
    }

    return 1;
}
