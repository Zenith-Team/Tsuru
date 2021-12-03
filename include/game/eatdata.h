#pragma once

#include <types.h>

class YoshiEatData {  // Size: 0x20
public:
    YoshiEatData(u32& id);

    virtual void* vf0C();
    virtual void* vf14(void*);
    virtual f32 vf1C(void*);
    virtual void* vf24(void*);
    virtual void vf2C();
    virtual bool handleEaten();
    virtual void vf3C();
    virtual void vf44();
    virtual u32 vf4C();
    virtual bool vf54(void*);
    virtual void* vf5C(void*);

    u32 ownerID;    // 0
    u32 _4;         // 4
    u32 state;      // 8
    u32 spitType;   // C
    sead::Vec3f scale;    // 10
    u32 _1C;        // 1C
};

class BabyYoshiEatData {  // Size: 0x20
public:
    BabyYoshiEatData(u32& id);

    virtual u32 vf0C();
    virtual void* vf14(void*);
    virtual void* vf1C(void*);
    virtual void vf24();
    virtual void vf2C();
    virtual bool handleEaten(void*);
    virtual void vf3C();

    u32 ownerID;        // 0
    u32 _4;             // 4
    sead::Vec3f scale;        // 8
    u32 _14;            // 14
    u32 isActive;       // 18
    u32 scoreReward;    // 1C
};
