#pragma once

#include "actor/actor.h"

class ActorBuffer {
public:
    ActorBase* findActorWithId(u32* id);

    sead::Buffer<ActorBase*> buffer;
    u32 usedCount;
    ActorBase** last;
    u32 _10;
    u8 _14;
};

class ActorMgr {
public:
    /* "addToActive":
       0: add to actorsToCreate
       1: add to activeActors and drawableActors
       else: don't add to any of the lists */
    ActorBase* create(ActorBuildInfo* buildInfo, u32 addToActive);

    static ActorMgr* instance;

    sead::IDisposer disposer;
    sead::UnitHeap* playerUnitHeap;
    sead::UnitHeap* actorUnitHeap;
    u8 deferredActorCreations[0x5970]; // sead::FixedRingBuffer<ActorBuildInfo, 520>
    ActorBase::ActorList actorsToCreate;
    ActorBase::ActorList actorsToDelete;
    ActorBase::ActorList activeActors;
    ActorBase::ActorList drawableActors;
    sead::FixedPtrArray<sead::Heap, 520> deletedActorHeaps;
    sead::FixedPtrArray<ActorBase, 520> finalExecuteList;
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
	Actor* owner;	// 18
};
