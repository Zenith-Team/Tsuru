#pragma once

#include "types.h"

class StageActor;

class YoshiEatData {  // Size: 0x24
public:
    YoshiEatData(u32& id);

    virtual void vf0C();
    virtual void vf14(StageActor*);
    virtual f32 vf1C(StageActor*);
    virtual void vf24(StageActor*);
    virtual void vf2C();
    virtual bool handleEaten();
    virtual void vf3C();
    virtual void vf44();
    virtual bool vf4C(StageActor*);
    virtual bool vf54(StageActor*);
    virtual void vf5C(StageActor*);

    u32 ownerID;    // 0
    u32 yoshiID;    // 4
    u32 state;      // 8
    u32 spitType;   // C
    Vec3f scale;    // 10
    u32 score;      // 1C
};

static_assert(sizeof(YoshiEatData) == 0x24, "YoshiEatData size mismatch");

class BabyYoshiEatData {  // Size: 0x24
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
    u32 babyYoshiID;    // 4
    Vec3f scale;        // 8
    u32 _14;            // 14
    u32 isActive;       // 18
    u32 scoreReward;    // 1C
};

static_assert(sizeof(BabyYoshiEatData) == 0x24, "BabyYoshiEatData size mismatch");
