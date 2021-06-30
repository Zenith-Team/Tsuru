#pragma once

#include "util/vec2i.h"
#include "util/vec3.h"
#include "sead.h"
#include "profile.h"
#include "actor/actorinfo.h"
#include "actor/actorbuildinfo.h"


class BaseActor {  // size: 0x50
    SEAD_RTTI_BASE(BaseActor)

public:
    BaseActor(const ActorBuildInfo* buildInfo);
    virtual ~BaseActor();

    virtual u32 beforeCreate();

    /*
       "onCreate()" return codes:
       0: Failure, delete (set isDeleted and call delete functions) if not created as deferred
       1: Success
       2: Failure, delete (set isDeleted and call delete functions) always
       Greater than 2: Failure, never delete

       If unsure, use 1 for success and 2 for failure
    */

    virtual u32 onCreate();
    virtual void afterCreate(u32);

    virtual u32 beforeExecute();
    virtual u32 onExecute();
    virtual void afterExecute(u32);
    virtual void finalExecute();

    virtual u32 beforeDraw();
    virtual u32 onDraw();
    virtual void afterDraw(u32);

    virtual u32 beforeDelete();
    virtual u32 onDelete();
    virtual void afterDelete(u32);

    void removeChild(BaseActor* child);
    ProfileId::ProfileIdType getProfileId();

    sead::Heap* heap;                               // 0
    u32 id;                                         // 4
    Profile* profile;                               // 8
    bool wasNotDeferred;                            // C
    bool isSprite;                                  // D
    bool isCreated;                                 // E
    bool isDeleted;                                 // F
    u32 settings1;                                  // 10
    u32 settings2;                                  // 14
    u8 movementId;                                  // 18
    u8 linkId;                                      // 19
    u8 initStateFlag;                               // 1A
    u8 _1B;                                         // 1B     //? Padding
    sead::OffsetList<BaseActor> childList;          // 1C
    sead::ListNode childNode;                       // 2C
    BaseActor* parent;                              // 34
    sead::ListNode actorListNode;                   // 38
    sead::ListNode drawListNode;                    // 40
    u32 flags;                                      // 48
};
