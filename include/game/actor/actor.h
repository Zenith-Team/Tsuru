#pragma once

#include "sead/runtimetypeinfo.h"
#include "game/actor/actorinfo.h"
#include "game/actor/actorbuildinfo.h"

class Actor { // Size: 0x50
    SEAD_RTTI_BASE(Actor)

public:
    Actor(const ActorBuildInfo* buildInfo);
    virtual ~Actor();

    virtual u32 beforeCreate();
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

    // Removes child actor from the childList
    void removeChild(Actor* child);

    // @return Profile ID of this actor
    u32 getProfileID();

    sead::Heap* heap;                       // 0
    u32 id;                                 // 4
    Profile* profile;                       // 8
    bool wasNotDeferred;                    // C
    bool isSprite;                          // D
    bool isCreated;                         // E
    bool isDeleted;                         // F
    u32 settings1;                          // 10
    u32 settings2;                          // 14
    u8 movementID;                          // 18
    u8 linkID;                              // 19
    u8 initialStateFlag;                    // 1A
    u8 _1B;                                 // 1B     //? Padding
    sead::OffsetList<Actor> childList;      // 1C
    sead::ListNode childNode;               // 2C
    Actor* parent;                          // 34
    sead::ListNode actorListNode;           // 38
    sead::ListNode drawListNode;            // 40
    u32 flags;                              // 48
};
