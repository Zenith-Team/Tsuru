#pragma once

#include <sead/runtimetypeinfo.h>
#include <game/actor/actorinfo.h>
#include <game/actor/actorbuildinfo.h>

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

    sead::Heap* heap;                       // _0
    u32 id;                                 // _4
    Profile* profile;                       // _8
    bool wasNotDeferred;                    // _C
    bool isSprite;                          // _D
    bool isCreated;                         // _E
    bool isDeleted;                         // _F
    union { u32 settings1;                  // _10
        struct {                            // _10
            u32 nybble12 : 4;               // _10
            u32 nybble11 : 4;               // _10
            u32 nybble10 : 4;               // _10
            u32 nybble9  : 4;               // _10
            u32 nybble8  : 4;               // _10
            u32 nybble7  : 4;               // _10
            u32 nybble6  : 4;               // _10
            u32 nybble5  : 4;               // _10
        };                                  // _10
    };                                      // _10
    union { u32 settings2;                  // _14
        struct {                            // _14
            u32 nybble20 : 4;               // _14
            u32 nybble19 : 4;               // _14
            u32 nybble18 : 4;               // _14
            u32 nybble17 : 4;               // _14
            u32 nybble16 : 4;               // _14
            u32 nybble15 : 4;               // _14
            u32 nybble14 : 4;               // _14
            u32 nybble13 : 4;               // _14
        };                                  // _14
    };                                      // _14
    u8 movementID;                          // _18
    u8 linkID;                              // _19
    u8 initialStateFlag;                    // _1A
    u8 _1B;                                 // _1B     //? Padding
    sead::OffsetList<Actor> childList;      // _1C
    sead::ListNode childNode;               // _2C
    Actor* parent;                          // _34
    sead::ListNode actorListNode;           // _38
    sead::ListNode drawListNode;            // _40
    u32 flags;                              // _48
};
