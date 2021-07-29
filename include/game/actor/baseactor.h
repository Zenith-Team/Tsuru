#pragma once

#include "sead.h"
#include "actorinfo.h"
#include "actorbuildinfo.h"

class BaseActor { // size: 0x50
    SEAD_RTTI_BASE(BaseActor)

public:
    BaseActor(const ActorBuildInfo* buildInfo);
    virtual ~BaseActor();

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

    void removeChild(BaseActor* child);
    ProfileID::ProfileIDType getProfileID();

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
    sead::OffsetList<BaseActor> mChildList;          // 1C
    sead::ListNode mChildNode;                       // 2C
    BaseActor* mParent;                              // 34
    sead::ListNode mActorListNode;                   // 38
    sead::ListNode mDrawListNode;                    // 40
    u32 mFlags;                                      // 48
};
