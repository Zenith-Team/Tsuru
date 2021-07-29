#pragma once

#include "sead.h"
#include "actor/stageactor.h"

class ActorBuffer { // Size: 0x18
public:
    ActorBuffer();

    BaseActor* findActorByID(u32* id);

    sead::Buffer<BaseActor*> mBuffer;
    u32 mUsedCount;
    BaseActor** mLast;
    u32 _10;
    u8 _14;
};

class ActorMgr {
public:
    BaseActor* create(ActorBuildInfo* buildInfo, u32 addToActive);
    BaseActor* instanciateActor(ActorBuildInfo* buildInfo, bool notDefer);
    
    u32 createActor(BaseActor* actor);  // Calls "create" virtual functions


    sead::IDisposer mDisposer;
    sead::UnitHeap* mPlayerUnitHeap;
    sead::UnitHeap* mActorUnitHeap;
    u8 mDeferredActorCreations[0x5970]; // sead::FixedRingBuffer<ActorBuildInfo, 520>
    sead::OffsetList<BaseActor> mActorsToCreate;
    sead::OffsetList<BaseActor> mActorsToDelete;
    sead::OffsetList<BaseActor> mActiveActors;
    sead::OffsetList<BaseActor> mDrawableActors;
    sead::FixedPtrArray<sead::Heap, 520> mDeletedActorHeaps;
    sead::FixedPtrArray<BaseActor, 520> mFinalExecuteList;
    ActorBuffer mActors;
    // ...

    static ActorMgr* sInstance;
};
