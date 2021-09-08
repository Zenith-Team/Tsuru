#pragma once

#include <sead.h>
#include <game/collision/tilechecker.h>

class StageActor;

class PhysicsMgr : public TileChecker { // Size: 0x14DC
    SEAD_RTTI_BASE(PhysicsMgr)

public:
    struct Sensor {
        f32 point1;             // _0
        f32 point2;             // _4
        f32 distanceFromCenter; // _8
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

    void init(StageActor* owner, const Sensor* belowSensor = nullptr, const Sensor* aboveSensor = nullptr, const Sensor* adjacentSensor = nullptr);
    void setSensor(const Sensor* sensor, u32 sensorID);
    const Sensor* getSensor(u32 sensorID) const;
    bool doExplosionAt(const Vec2f& topLeft, const Vec2f& bottomRight);

    inline bool isOnGround()      { return this->output & FlagOnGround;      }
    inline bool isCollidedRight() { return this->output & FlagCollidedRight; }
    inline bool isCollidedLeft()  { return this->output & FlagCollidedLeft;  }
    inline bool isCollided(u32 direction) {
        if (direction > 1) return false;
        return this->output & (FlagCollidedRight << direction);
    }

    u8 _4C[0x844];               // 4C
    StageActor* owner;           // 890
    u32 _894;                    // 894
    Vec3f* position;             // 898  &owner->position
    Vec3f* _89C;                 // 89C  &owner->_240, lastPosition?
    u8* layer;                   // 8A0  &owner->layer
    u8* collisionMask;           // 8A4  &owner->collisionMask
    s8* playerID;                // 8A8  &owner->playerID
    u32 output;                  // 8AC
    u8 _8B0[0x64];               // 8B0
    u8 _914;                     // 914
    bool hasBeenInited;          // 915
    bool _916;                   // 916
    bool _917;                   // 917
    bool _918;                   // 918
    bool sensorIsSet[4];         // 919
    bool sensorIsNull[4];        // 91D
    bool _921[4];                // 921
    union {
        struct {
            Sensor rightSensor;  // 928
            Sensor leftSensor;   // 934
            Sensor aboveSensor;  // 940
            Sensor belowSensor;  // 94C
        };

        Sensor sensors[4];
    };

    u8 _958[0xB84];              // 958
};
