#pragma once

#include "actor/stageactor.h"

class ActorBuffer {
public:
    BaseActor* findActorWithId(u32* id);

    sead::Buffer<BaseActor*> buffer;
    u32 usedCount;
    BaseActor** last;
    u32 _10;
    u8 _14;
};

class ActorMgr {
public:
    /* "addToActive":
       0: add to actorsToCreate
       1: add to activeActors and drawableActors
       else: don't add to any of the lists */
    BaseActor* create(ActorBuildInfo* buildInfo, u32 addToActive);

    static ActorMgr* instance;

    sead::IDisposer disposer;
    sead::UnitHeap* playerUnitHeap;
    sead::UnitHeap* actorUnitHeap;
    u8 deferredActorCreations[0x5970]; // sead::FixedRingBuffer<ActorBuildInfo, 520>
    BaseActor::ActorList actorsToCreate;
    BaseActor::ActorList actorsToDelete;
    BaseActor::ActorList activeActors;
    BaseActor::ActorList drawableActors;
    sead::FixedPtrArray<sead::Heap, 520> deletedActorHeaps;
    sead::FixedPtrArray<BaseActor, 520> finalExecuteList;
    ActorBuffer actors;
    // ...
};

class ActorScaler {  // size: 0x1C
public:
    virtual void getScale();

	Vec3 scale;		// 0
	f32 _C;			// C
	u32 _10;		// 10
	u32 _14;		// 14
	StageActor* owner;	// 18
};
