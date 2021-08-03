#include "log.h"
#include "game/eventmgr.h"
#include "game/actor/actormgr.h"
#include "game/profile/profileid.h"
#include "game/actor/stage/stageactor.h"

class ActorSpawner : public StageActor {
public:
    ActorSpawner(const ActorBuildInfo* buildInfo);
    virtual ~ActorSpawner() { }

    static BaseActor* build(const ActorBuildInfo* buildInfo);

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

BaseActor* ActorSpawner::build(const ActorBuildInfo* buildInfo) {
    return new ActorSpawner(buildInfo);
}

u32 ActorSpawner::onCreate() {
    if (!mEventID2)
        return 2;
    
    u16 inputID = mLinkID | ((mMovementID & 0xF) << 8);

    if (mMovementID & 0x10)
        mSpawnProfileID = Profile::spriteToProfileList[inputID];
    else
        mSpawnProfileID = inputID;

    // Call onExecute to prevent the spawned actor to be missing for one frame if the event is already active
    return onExecute();
}

u32 ActorSpawner::onExecute() {
    BaseActor* child = (mChildList.begin() != mChildList.end()) ? mChildList.begin().mPtr : nullptr;

    if (EventMgr::sInstance->isActive(mEventID2-1)) {
        if (mInitialStateFlag == 2 && child) {
            StageActor* actor = sead::DynamicCast<StageActor, BaseActor>(child);

            if (actor) {
                actor->mIsActive = true;
                actor->mIsVisible = true;
                actor->addHitboxColliders();
            }

            return 1;
        }

        if (!mSpawned) {
            ActorBuildInfo buildInfo = { 0 };

            buildInfo.mSettings1 = mSettings1;
            buildInfo.mSettings2 = mSettings2;
            buildInfo.mProfile = Profile::get(mSpawnProfileID);
            buildInfo.mPosition = mPosition;
            buildInfo.mEventID1 = mEventID1 & 0xF;
            buildInfo.mEventID2 = (mEventID1 >> 4) & 0xF;
            ActorMgr::sInstance->create(&buildInfo, 0);

            mSpawned = true;
        }
    }

    else {
        if (mInitialStateFlag == 1 && child) {
            child->mIsDeleted = true;
        }

        else if (mInitialStateFlag == 2 && child) {
            StageActor* actor = sead::DynamicCast<StageActor, BaseActor>(child);

            if (actor) {
                actor->mIsActive = false;
                actor->mIsVisible = false;
                actor->removeHitboxColliders();
            }
        }

        mSpawned = false;
    }

    return 1;
}
