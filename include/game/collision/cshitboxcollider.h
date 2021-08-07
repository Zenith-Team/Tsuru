// This is an unfortunate filename...

#pragma once

#include "sead.h"
#include "types.h"

class CSHitboxCollider {
public:
    struct Info {
        f32 mSize;
        Vec3f mOffset;
    };

public:
    CSHitboxCollider();
    virtual ~CSHitboxCollider();

    void init(void*, f32*);
    void add(CSHitboxCollider*);

    u32 mOwnerID;
    u32 _4;
    Info mInfo;
};

class CSHitboxColliderMgr {
    SEAD_SINGLETON_DISPOSER(CSHitboxColliderMgr)

public:
    struct UnknownStruct : public sead::PtrArrayImpl {
        u8 unk1[1032];
    };

public:
    void updateColliders();

    UnknownStruct unk1;
    UnknownStruct unk2;
};
