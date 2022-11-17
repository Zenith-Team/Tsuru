#include "game/actor/stage/stageactor.h"
#include "game/actor/actormgr.h"
#include "game/eventmgr.h"

class ActorSpawner : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(ActorSpawner, StageActor);

public:
    ActorSpawner(const ActorBuildInfo* buildInfo);
    virtual ~ActorSpawner() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;

    Actor* child;
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
    if (!this->eventID1) {
        return 2;
    }

    this->child = nullptr;

    u16 inputID = linkID | ((movementID & 0xF) << 8);

    if (movementID & 0x10) {
        this->spawnProfileID = Profile::sprite(inputID);
    } else {
        this->spawnProfileID = inputID;
    }

    return this->onExecute();
}

u32 ActorSpawner::onExecute() {
    if (EventMgr::instance()->isActive(this->eventID1 - 1)) {
        if (initialStateFlag == 2 && this->child) {
            StageActor* actor = sead::DynamicCast<StageActor, Actor>(this->child);

            if (actor) {
                actor->isActive = true;
                actor->isVisible = true;
                actor->addHitboxColliders();
            }

            return 1;
        }

        if (!this->spawned) {
            ActorBuildInfo buildInfo = { 0 };

            buildInfo.settings1 = this->settings1;
            buildInfo.settings2 = this->settings2;
            buildInfo.profile = Profile::get(this->spawnProfileID);
            buildInfo.position = this->position;
            buildInfo.eventID1 = (this->eventID2 >> 4) & 0xF;
            buildInfo.eventID2 = this->eventID2 & 0xF;
            buildInfo.parentID = this->id;
            this->child = ActorMgr::instance()->create(buildInfo, 0);

            this->spawned = true;
        }
    }

    else {
        if (this->initialStateFlag == 1 && this->child) {
            this->child->isDeleted = true;
            this->child = nullptr;
        }

        else if (this->initialStateFlag == 2 && this->child) {
            StageActor* actor = sead::DynamicCast<StageActor, Actor>(this->child);

            if (actor) {
                actor->isActive = false;
                actor->isVisible = false;
                actor->removeHitboxColliders();
            }
        }

        this->spawned = false;
    }

    return 1;
}
