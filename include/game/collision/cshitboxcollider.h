// This is an unfortunate filename...

#pragma once

#include <sead.h>
#include <types.h>

class CSCollisionActor;

class CSHitboxCollider {
public:
    struct Info {
        f32 size;
        sead::Vec3f offset;
    };

public:
    CSHitboxCollider();
    virtual ~CSHitboxCollider();

    // Initializes the collider
    // @param owner Pointer to owner of the hitbox
    // @param info Pointer to collider info struct
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
    // Updates all currently active colliders
    void updateColliders();
    void add(CSHitboxCollider* cshc);
    // Return type unknown
    s32 FUN_21c5894(CSHitboxCollider* cshc);

    UnknownStruct array1;
    UnknownStruct array2;
};
