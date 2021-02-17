#pragma once

#include "util/vec2i.h"
#include "util/vec3.h"
#include "sead.h"
#include "profile.h"

class ActorInfo
{
public:
    enum Flags
    {
        FlagIgnoreSpawnRange = 0x002,
        FlagUnknown          = 0x008,
        FlagGrouped          = 0x010,
        FlagUnknown2         = 0x100
    };

public:
    static ActorInfo Default;

    s32 xoffs;                    // 0
    s32 yoffs;                    // 4
    Vec2i spawnRangeOffset;       // 8
    Vec2i spawnRangeSize;         // 10
    u16 _18;                      // 18
    u16 _1A;                      // 1A
    u16 _1C;                      // 1C
    u16 _1E;                      // 1E
    u16 flags;                    // 20
};

struct ActorBuildInfo
{
    u32 settings1;                // 0
    u32 settings2;                // 4
    u32 parentId;                 // 8
    Profile* profile;             // C
    Vec3 position;                // 10
    u32 rotation;                 // 1C
    u8 layer;                     // 20
    u8 eventId1;                  // 21
    u8 eventId2;                  // 22
    u8 pad1;                      // 23
    u8 movementId;                // 24
    u8 linkId;                    // 25
    u8 initStateFlag;             // 26
    u8 pad2;                      // 27
    u8* _28;                      // 28
};


class Base
{
    SEAD_RTTI_BASE(Base)

public:
    Base(const ActorBuildInfo* buildInfo);
    virtual ~Base();

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

    typedef sead::OffsetList<Base> ActorList;

    sead::Heap* heap;             // 0
    u32 id;                       // 4
    Profile* profile;             // 8
    bool wasNotDeferred;          // C
    bool isSprite;                // D
    bool isCreated;               // E
    bool isDeleted;               // F
    u32 settings1;                // 10
    u32 settings2;                // 14
    u8 movementId;                // 18
    u8 linkId;                    // 19
    u8 initStateFlag;             // 1A
    ActorList childList;          // 1C
    sead::ListNode childNode;     // 2C
    Base* parent;                 // 34
    sead::ListNode actorListNode; // 38
    sead::ListNode drawListNode;  // 40
    u32 flags;                    // 48
};
