#pragma once

#include "sead.h"
#include "actor/actorbase.h"

class ActorList {
public:
	u32 maxCount;
	ActorBase** first;
	u32 usedCount;
	ActorBase** last;
	u32 actorId;
	u32 _14;

	ActorBase* findActorById(u32* id);
};

class ActorMgr : public sead::IDisposer {
public:
    static ActorMgr* instance;

    /* "addToActive":
       0: add to actorsToCreate
       1: add to activeActors and drawableActors
       else: don't add to any of the lists
    */
    ActorBase* create(ActorBuildInfo* buildInfo, u32 addToActive);
    ActorBase** findActorByType(ProfileId::ProfileIdType actorId, ActorBase**);

    // TODO
    void* playerUnitHeap;
	void* actorUnitHeap;
	u8 _18[0x5988-0x18];
	sead::ListImpl createList;
	sead::ListImpl deleteList;
	sead::ListImpl activeActors;
	sead::ListImpl drawnActors;
	u8 _59C8[0x6A20-0x59C8];
	ActorList actorList;
	u8 _6A38[0x6A44-0x6A38];
};
