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

    sead::Heap* mHeap;                               // 0
    u32 mID;                                         // 4
    Profile* mProfile;                               // 8
    bool mWasNotDeferred;                            // C
    bool mIsSprite;                                  // D
    bool mIsCreated;                                 // E
    bool mIsDeleted;                                 // F
    u32 mSettings1;                                  // 10
    u32 mSettings2;                                  // 14
    u8 mMovementID;                                  // 18
    u8 mLinkID;                                      // 19
    u8 mInitialStateFlag;                            // 1A
    u8 _1B;                                          // 1B     //? Padding
    sead::OffsetList<Actor> mChildList;          // 1C
    sead::ListNode mChildNode;                       // 2C
    Actor* mParent;                              // 34
    sead::ListNode mActorListNode;                   // 38
    sead::ListNode mDrawListNode;                    // 40
    u32 mFlags;                                      // 48
};
