#pragma once

#include <sead.h>
#include <game/actor/actorinfo.h>
#include <game/actor/actorbuildinfo.h>

class Actor { // size: 0x50
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

    void removeChild(Actor* child);
    u32 getProfileID();

    sead::Heap* mHeap;                      // _0
    u32 mID;                                // _4
    Profile* mProfile;                      // _8
    bool mWasNotDeferred;                   // _C
    bool mIsSprite;                         // _D
    bool mIsCreated;                        // _E
    bool mIsDeleted;                        // _F
    union { u32 mSettings1;                 // _10
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
    union { u32 mSettings2;                 // _14
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
    u8 mMovementID;                         // _18
    u8 mLinkID;                             // _19
    u8 mInitialStateFlag;                   // _1A
    u8 _1B;                                 // _1B     //? Padding
    sead::OffsetList<Actor> mChildList;     // _1C
    sead::ListNode mChildNode;              // _2C
    Actor* mParent;                         // _34
    sead::ListNode mActorListNode;          // _38
    sead::ListNode mDrawListNode;           // _40
    u32 mFlags;                             // _48
};
