#pragma once

#include <sead.h>
#include <game/actor/stage/stageactor.h>

class ActorBuffer { // Size: 0x18
public:
    ActorBuffer();

    ActorBase* findActorByID(u32* id);

    sead::Buffer<ActorBase*> mBuffer;
    u32 mUsedCount;
    ActorBase** mLast;
    u32 _10;
    u8 _14;
};

class ActorMgr {
public:
    ActorBase* create(ActorBuildInfo* buildInfo, u32 addToActive);
    ActorBase* instanciateActor(ActorBuildInfo* buildInfo, bool notDefer);
    
    u32 createActor(ActorBase* actor);  // Calls "create" virtual functions


    sead::IDisposer mDisposer;
    sead::UnitHeap* mPlayerUnitHeap;
    sead::UnitHeap* mActorUnitHeap;
    u8 mDeferredActorCreations[0x5970]; // sead::FixedRingBuffer<ActorBuildInfo, 520>
    sead::OffsetList<ActorBase> mActorsToCreate;
    sead::OffsetList<ActorBase> mActorsToDelete;
    sead::OffsetList<ActorBase> mActiveActors;
    sead::OffsetList<ActorBase> mDrawableActors;
    sead::FixedPtrArray<sead::Heap, 520> mDeletedActorHeaps;
    sead::FixedPtrArray<ActorBase, 520> mFinalExecuteList;
    ActorBuffer mActors;
    // ...

    static ActorMgr* sInstance;
};
