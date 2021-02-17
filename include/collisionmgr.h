#pragma once

#include "actor/actor.h"
#include "tilecheck.h"

class CollisionMgr : public TileCheck
{
    SEAD_RTTI_BASE(CollisionMgr)

public:
    struct Sensor
    {
        f32 p1;
        f32 p2;
        f32 distanceFromCenter;
    };

    enum Flags
    {
        FlagOnGround        = 1 << 0,
        FlagOnSlope         = 1 << 1,
        FlagOnSemiSold      = 1 << 4,
        FlagCollidedRight   = 1 << 18,
        FlagCollidedLeft    = 1 << 19
    };

public:
    CollisionMgr();
    virtual ~CollisionMgr();

    virtual void process();
    virtual void vf2C();
    virtual void vf34();
    virtual u32 vf3C() = 0;
    virtual u32 vf44() = 0;
    virtual u32 vf4C() = 0;
    virtual void vf54();
    virtual void vf5C();
    virtual void vf64();
    virtual void vf6C();

    void init(Actor* owner, const Sensor* belowSensor, const Sensor* aboveSensor, const Sensor* adjacentSensor);
    void setSensor(const Sensor* sensor, u32 sensorId);
    const Sensor* getSensor(u32 sensorId) const;
    bool doExplosionAt(const Vec2& topLeft, const Vec2& bottomRight);

    inline bool isOnGround()      { return output & FlagOnGround; }
    inline bool isCollidedRight() { return output & FlagCollidedRight; }
    inline bool isCollidedLeft()  { return output & FlagCollidedLeft; }

    inline bool isCollided(u32 direction)
    {
        if (direction > 1) return false;
        return output & (FlagCollidedRight << direction);
    }



    u8 _unk4C[0x890-0x4C];      // 4C

    Actor* owner;               // 890
    u32 _894;                   // 894
    Vec3* position;             // 898  &owner->position
    Vec3* _89C;                 // 89C  &owner->_240, lastPosition?
    u8* layer;                  // 8A0  &owner->layer
    u8* collisionMask;          // 8A4  &owner->collisionMask
    s8* playerId;               // 8A8  &owner->playerId
    u32 output;                 // 8AC

    u8 _unk8B0[0x914-0x8B0];    // 8B0

    u8 _914;                    // 914
    bool hasBeenInited;         // 915
    bool _916;                  // 916
    bool _917;                  // 917
    bool _918;                  // 918
    bool sensorIsSet[4];        // 919
    bool sensorIsNull[4];       // 91D
    bool _921[4];               // 921

    union
    {
        struct
        {
            Sensor rightSensor;         // 928
            Sensor leftSensor;          // 934
            Sensor aboveSensor;         // 940
            Sensor belowSensor;         // 94C
        };

        Sensor sensors[4];
    };

    u8 _unk958[0x14DC-0x958];   // 958
};


class ActorCollisionMgr : public CollisionMgr
{
    SEAD_RTTI_OVERRIDE(ActorCollisionMgr, CollisionMgr)

public:
    ActorCollisionMgr();

    u32 vf3C() override;
    u32 vf44() override;
    u32 vf4C() override;
};
