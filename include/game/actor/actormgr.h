#pragma once

#include <sead.h>
#include <game/actor/stage/stageactor.h>

class ActorBuffer { // Size: 0x18
public:
    ActorBuffer();

    Actor* findActorByID(u32* id);

    sead::Buffer<Actor*> startBuffer;
    sead::Buffer<Actor*> endBuffer;
    u32 _10;
    u8  _14;
};

class ActorMgr {
    SEAD_SINGLETON_DISPOSER(ActorMgr)

public:
    Actor* create(ActorBuildInfo* buildInfo, u32 addToActive);
    Actor* instanciateActor(ActorBuildInfo* buildInfo, bool notDefer);

    u32 createActor(Actor* actor);  // Calls "create" virtual functions

    sead::UnitHeap* playerUnitHeap;
    sead::UnitHeap* actorUnitHeap;
    u8 deferredActorCreations[0x5970]; // sead::FixedRingBuffer<ActorBuildInfo, 520>
    sead::OffsetList<Actor> actorsToCreate;
    sead::OffsetList<Actor> actorsToDelete;
    sead::OffsetList<Actor> activeActors;
    sead::OffsetList<Actor> drawableActors;
    sead::FixedPtrArray<sead::Heap, 520> deletedActorHeaps;
    sead::FixedPtrArray<Actor, 520> finalExecuteList;
    ActorBuffer actors;
    // ...
};
