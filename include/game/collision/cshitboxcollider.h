// This is an unfortunate filename...

#pragma once

#include <sead.h>
#include <types.h>

class CSCollisionActor;

class CSHitboxCollider {
public:
    struct Info {
        f32 mSize;
        Vec3f mOffset;
    };

public:
    CSHitboxCollider();
    virtual ~CSHitboxCollider();

    void init(CSCollisionActor* owner, const Info* info);

    u32 mOwnerID;
    u32 _4;
    Info mInfo;
};

class CSHitboxColliderMgr {
    SEAD_SINGLETON_DISPOSER(CSHitboxColliderMgr)

public:
    struct UnknownStruct : public sead::PtrArrayImpl {
        u8 data[1032];
    };

public:
    void updateColliders();
    void add(CSHitboxCollider* cshc);
    s32 FUN_21c5894(CSHitboxCollider* cshc);    // Return type unknown

    UnknownStruct mArray1;
    UnknownStruct mArray2;
};
