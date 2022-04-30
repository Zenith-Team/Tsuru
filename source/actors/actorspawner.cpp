#include "log.h"
#include "game/eventmgr.h"
#include "game/actor/actormgr.h"
#include "game/profile/profileid.h"
#include "game/actor/stage/stageactor.h"

class ActorSpawner : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(ActorSpawner, StageActor)

public:
    ActorSpawner(const ActorBuildInfo* buildInfo);
    virtual ~ActorSpawner() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;

    u16 spawnProfileID;
    bool spawned;
};

const Profile ActorSpawnerProfile(&ActorSpawner::build, ProfileID::ActorSpawner);

ActorSpawner::ActorSpawner(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
    , spawned(false)
{ }

Actor* ActorSpawner::build(const ActorBuildInfo* buildInfo) {
    return new ActorSpawner(buildInfo);
}

u32 ActorSpawner::onCreate() {
    if (!eventID1)
        return 2;

    u16 inputID = linkID | ((movementID & 0xF) << 8);

    if (movementID & 0x10)
        spawnProfileID = Profile::spriteToProfileList[inputID];
    else
        spawnProfileID = inputID;

    // Call onExecute to prevent the spawned actor to be missing for one frame if the event is already active
    return onExecute();
}

u32 ActorSpawner::onExecute() {
    Actor* child = (childList.begin() != childList.end()) ? childList.begin().ptr : nullptr;

    if (EventMgr::instance()->isActive(this->eventID1 - 1)) {
        if (initialStateFlag == 2 && child) {
            StageActor* actor = sead::DynamicCast<StageActor, Actor>(child);

            if (actor) {
                actor->isActive = true;
                actor->isVisible = true;
                actor->addHitboxColliders();
            }

            return 1;
        }

        if (!spawned) {
            ActorBuildInfo buildInfo = { 0 };

            buildInfo.settings1 = this->settings1;
            buildInfo.settings2 = this->settings2;
            buildInfo.profile = Profile::get(this->spawnProfileID);
            buildInfo.position = this->position;
            buildInfo.eventID1 = (this->eventID2 >> 4) & 0xF;
            buildInfo.eventID2 = this->eventID2 & 0xF;
            ActorMgr::instance()->create(buildInfo, 0);

            this->spawned = true;
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

        spawned = false;
    }

    return 1;
}
