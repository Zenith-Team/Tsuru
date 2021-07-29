#pragma once

#include "sead.h"
#include "tilechecker.h"

class StageActor;

class PhysicsMgr : public TileChecker {
    SEAD_RTTI_BASE(PhysicsMgr)

public:
    struct Sensor {
        f32 mPoint1;             // _0
        f32 mPoint2;             // _4
        f32 mDistanceFromCenter; // _8
    };

    enum Flags {
        FlagOnGround        = 1 << 0,
        FlagOnSlope         = 1 << 1,
        FlagOnSemiSold      = 1 << 4,
        FlagCollidedRight   = 1 << 18,
        FlagCollidedLeft    = 1 << 19
    };

    PhysicsMgr();

    virtual ~PhysicsMgr();
    virtual void processCollisions();
    virtual void vf2C();
    virtual void vf34();
    virtual u32 vf3C() = 0;
    virtual u32 vf44() = 0;
    virtual u32 vf4C() = 0;
    virtual void vf54();
    virtual void vf5C();
    virtual void vf64();
    virtual void vf6C();

    void init(StageActor* owner, const Sensor* belowSensor, const Sensor* aboveSensor, const Sensor* adjacentSensor);
    void setSensor(const Sensor* sensor, u32 sensorID);
    const Sensor* getSensor(u32 sensorID) const;
    bool doExplosionAt(const Vec2f& topLeft, const Vec2f& bottomRight);

    inline bool isOnGround() { return this->mOutput & OnGround; }

    u8 _unk4C[0x890-0x4C];       // 4C
    StageActor* mOwner;          // 890
    u32 _894;                    // 894
    Vec3f* mPosition;            // 898  &owner->position
    Vec3f* _89C;                 // 89C  &owner->_240, lastPosition?
    u8* mLayer;                  // 8A0  &owner->layer
    u8* mCollisionMask;          // 8A4  &owner->collisionMask
    s8* mPlayerID;               // 8A8  &owner->playerId
    u32 mOutput;                 // 8AC
    u8 _unk8B0[0x914-0x8B0];     // 8B0
    u8 _914;                     // 914
    bool mHasBeenInited;         // 915
    bool _916;                   // 916
    bool _917;                   // 917
    bool _918;                   // 918
    bool mSensorIsSet[4];        // 919
    bool mSensorIsNull[4];       // 91D
    bool _921[4];                // 921
    union {
        struct {
            Sensor mRightSensor; // 928
            Sensor mLeftSensor;  // 934
            Sensor mAboveSensor; // 940
            Sensor mBelowSensor; // 94C
        };

        Sensor mSensors[4];
    };

    u8 _unk958[0x14DC-0x958];    // 958
};
