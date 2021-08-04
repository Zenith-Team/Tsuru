#pragma once

#include "types.h"

class CSHitboxCollider {
public:
    CSHitboxCollider();
    virtual ~CSHitboxCollider();

    void init(void*, f32*);

    u8 unk1[4];
    u32 _4;
    f32 _8;
    void* _C;
    void* _10;
    void* _14;
};
