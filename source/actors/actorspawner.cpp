#include <log.h>
#include <game/eventmgr.h>
#include <game/actor/actormgr.h>
#include <game/profile/profileid.h>
#include <game/actor/stage/stageactor.h>

class ActorSpawner : public StageActor {
public:
    ActorSpawner(const ActorBuildInfo* buildInfo);
    virtual ~ActorSpawner() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;

    u16 spawnProfileID;
    bool spawned;
};

const Profile ActorSpawnerProfile(&ActorSpawner::build, ProfileID::ActorSpawner, "ActorSpawner", nullptr, 0);

ActorSpawner::ActorSpawner(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
    , spawned(false)
{ }

Actor* ActorSpawner::build(const ActorBuildInfo* buildInfo) {
    return new ActorSpawner(buildInfo);
}

u32 ActorSpawner::onCreate() {
    if (!eventID2)
        return 2;
    
    u16 inputID = mLinkID | ((mMovementID & 0xF) << 8);

    if (mMovementID & 0x10)
        this->spawnProfileID = Profile::spriteToProfileList[inputID];
    else
        this->spawnProfileID = inputID;

    // Call onExecute to prevent the spawned actor to be missing for one frame if the event is already active
    return onExecute();
}

u32 ActorSpawner::onExecute() {
    Actor* child = (mChildList.begin() != mChildList.end()) ? mChildList.begin().mPtr : nullptr;

    if (EventMgr::instance()->isActive(eventID2-1)) {
        if (mInitialStateFlag == 2 && child) {
            StageActor* actor = sead::DynamicCast<StageActor, Actor>(child);

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
            buildInfo.mProfile = Profile::get(this->spawnProfileID);
            buildInfo.position = this->position;
            buildInfo.eventID1 = this->eventID1 & 0xF;
            buildInfo.eventID2 = (this->eventID1 >> 4) & 0xF;
            ActorMgr::instance()->create(&buildInfo, 0);

            this->spawned = true;
        }
    }

    else {
        if (mInitialStateFlag == 1 && child) {
            child->isDeleted = true;
        }

        else if (mInitialStateFlag == 2 && child) {
            StageActor* actor = sead::DynamicCast<StageActor, Actor>(child);

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
