#pragma once

#include <sead.h>
#include <game/actor/stage/stageactor.h>

class ActorBuffer { // Size: 0x18
public:
    ActorBuffer();

    Actor* findActorByID(u32* id);

    sead::Buffer<Actor*> mStartBuffer;
    sead::Buffer<Actor*> mEndBuffer;
    u32 _10;
    u8 _14;
};

class ActorMgr {
    SEAD_SINGLETON_DISPOSER(ActorMgr)

public:
    Actor* create(ActorBuildInfo* buildInfo, u32 addToActive);
    Actor* instanciateActor(ActorBuildInfo* buildInfo, bool notDefer);
    
    u32 createActor(Actor* actor);  // Calls "create" virtual functions


    sead::UnitHeap* mPlayerUnitHeap;
    sead::UnitHeap* mActorUnitHeap;
    u8 mDeferredActorCreations[0x5970]; // sead::FixedRingBuffer<ActorBuildInfo, 520>
    sead::OffsetList<Actor> mActorsToCreate;
    sead::OffsetList<Actor> mActorsToDelete;
    sead::OffsetList<Actor> mActiveActors;
    sead::OffsetList<Actor> mDrawableActors;
    sead::FixedPtrArray<sead::Heap, 520> mDeletedActorHeaps;
    sead::FixedPtrArray<Actor, 520> mFinalExecuteList;
    ActorBuffer mActors;
    // ...
};
