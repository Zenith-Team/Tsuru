// This is an unfortunate filename...

#pragma once

#include <sead.h>
#include <types.h>

class CSCollisionActor;

class CSHitboxCollider {
public:
    struct Info {
        f32 size;
        Vec3f offset;
    };

public:
    CSHitboxCollider();
    virtual ~CSHitboxCollider();

    void init(CSCollisionActor* owner, const Info* info);

    u32 ownerID;
    u32 _4;
    Info info;
};

class CSHitboxColliderMgr {
    SEAD_SINGLETON_DISPOSER(CSHitboxColliderMgr)

public:
    struct UnknownStruct : public sead::PtrArrayImpl {
        u8 _C[1032];
    };

public:
    void updateColliders();
    void add(CSHitboxCollider* cshc);
    s32 FUN_21c5894(CSHitboxCollider* cshc);    // Return type unknown

    UnknownStruct array1;
    UnknownStruct array2;
};
