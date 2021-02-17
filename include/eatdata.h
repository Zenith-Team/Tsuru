#pragma once

#include "util/vec3.h"

class YoshiEatData
{
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

    u32 ownerId;
    u32 _4;
    u32 state;
    u32 spitType;
    Vec3 scale;
    u32 _1C;
};

class BabyYoshiEatData
{
public:
    BabyYoshiEatData(u32& id);

    virtual u32 vf0C();
    virtual void* vf14(void*);
    virtual void* vf1C(void*);
    virtual void vf24();
    virtual void vf2C();
    virtual bool handleEaten(void*);
    virtual void vf3C();

    u32 ownerId;
    u32 _4;
    Vec3 scale;
    u32 _14;
    u32 isActive;
    u32 scoreReward;
};
