#include <log.h>
#include <game/eventmgr.h>
#include <game/actor/actormgr.h>
#include <game/profile/profileid.h>
#include <game/actor/stage/stageactor.h>

class ActorSpawner : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(ActorSpawner, StageActor)

public:
    ActorSpawner(const ActorBuildInfo* buildInfo);
    virtual ~ActorSpawner() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;

    u16 mSpawnProfileID;
    bool mSpawned;
};

const Profile ActorSpawnerProfile(&ActorSpawner::build, ProfileID::ActorSpawner, "ActorSpawner", nullptr, 0);

ActorSpawner::ActorSpawner(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
    , mSpawned(false)
{ }

Actor* ActorSpawner::build(const ActorBuildInfo* buildInfo) {
    return new ActorSpawner(buildInfo);
}

u32 ActorSpawner::onCreate() {
    if (!eventID2)
        return 2;
    
    u16 inputID = linkID | ((movementID & 0xF) << 8);

    if (movementID & 0x10)
        mSpawnProfileID = Profile::spriteToProfileList[inputID];
    else
        mSpawnProfileID = inputID;

    // Call onExecute to prevent the spawned actor to be missing for one frame if the event is already active
    return onExecute();
}

u32 ActorSpawner::onExecute() {
    Actor* child = (childList.begin() != childList.end()) ? childList.begin().ptr : nullptr;

    if (EventMgr::instance()->isActive(eventID2-1)) {
        if (initialStateFlag == 2 && child) {
            StageActor* actor = sead::DynamicCast<StageActor, Actor>(child);

            if (actor) {
                actor->isActive = true;
                actor->isVisible = true;
                actor->addHitboxColliders();
            }

            return 1;
        }

        if (!mSpawned) {
            ActorBuildInfo buildInfo = { 0 };

            buildInfo.settings1 = settings1;
            buildInfo.settings2 = settings2;
            buildInfo.profile = Profile::get(mSpawnProfileID);
            buildInfo.position = position;
            buildInfo.eventID1 = eventID1 & 0xF;
            buildInfo.eventID2 = (eventID1 >> 4) & 0xF;
            ActorMgr::instance()->create(&buildInfo, 0);

            mSpawned = true;
        }
    }

    else {
        if (initialStateFlag == 1 && child) {
            child->isDeleted = true;
        }

        else if (initialStateFlag == 2 && child) {
            StageActor* actor = sead::DynamicCast<StageActor, Actor>(child);

            if (actor) {
                actor->isActive = false;
                actor->isVisible = false;
                actor->removeHitboxColliders();
            }
        }

        mSpawned = false;
    }

    return 1;
}
