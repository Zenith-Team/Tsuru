#pragma once

#include "sead/list.h"
#include "sead/heap.h"
#include "sead/buffer.h"
#include "sead/ptrarray.h"
#include "game/actor/stage/stageactor.h"

class ActorBuffer { // Size: 0x18
public:
    ActorBuffer(sead::Heap* heap, s32 size);

    // Locates an actor by the Actor ID
    // @param id Actor ID of the intended target actor
    // @return Pointer to located actor
    Actor* findActorByID(const u32& id);

    void addActor(Actor* actor);

    sead::Buffer<Actor*> start;
    sead::Buffer<Actor*> end;
    u32 _10;
    u8  _14;
};

class ActorMgr { // Size: 0x6A44
    SEAD_SINGLETON_DISPOSER(ActorMgr);

public:
    // Spawns an actor in the current level
    // @param buildInfo ActorBuildInfo to build the actor with
    // @param addToActive 0: Add to actorsToCreate, 1: add to activeActors and drawableActors, Else: Don't add to any list
    // @return Pointer to created actor
    Actor* create(ActorBuildInfo& buildInfo, u32 addToActive = 0);

    // Creates an instance of an actor class using the build info
    // @param buildInfo ActorBuildInfo to build the actor with
    // @return Pointer to created actor
    Actor* instanciateActor(const ActorBuildInfo& buildInfo, bool dontDefer);

    // Creates and set player and actor unit heaps via sead::UnitHeap::tryCreateWithBlockNum
    void createHeaps(sead::Heap* heap);

    // Calls "create" virtual functions
    // @param Pointer to actor to call the functions on
    u32 createActor(Actor* actor);

    // Calls "execute" virtual functions
    void executeActors();

    // Calls "draw" virtual functions
    void drawActors();

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
    u32 currentID;
    bool currentWasNotDeferred;
    // ...
};
