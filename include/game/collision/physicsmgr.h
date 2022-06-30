#pragma once

#include "sead.h"
#include "game/collision/tilechecker.h"

class StageActor;

class PhysicsMgr : public TileChecker { // Size: 0x14E0
    SEAD_RTTI_BASE(PhysicsMgr);

public:
    struct Sensor {
        f32 point1;             // 0
        f32 point2;             // 4
        f32 distanceFromCenter; // 8
    };

public:
    enum Flags {
        Flag_OnGround        = 1 << 0,
        Flag_OnSlope         = 1 << 1,
        Flag_OnSemiSold      = 1 << 4,
        Flag_CollidedRight   = 1 << 18,
        Flag_CollidedLeft    = 1 << 19
    };

public:
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

    // Initializes the physics manager
    // @param owner Pointer to the owner of the manager
    // @param belowSensor Optional pointer to a sensor to be used as the bottom sensor
    // @param aboveSensor Optional pointer to a sensor to be used as the top sensor
    // @param adjacentSensor Optional pointer to a sensor to be used as the side sensors
    void init(StageActor* owner, const Sensor* belowSensor = nullptr, const Sensor* aboveSensor = nullptr, const Sensor* adjacentSensor = nullptr);
    // Sets a sensor
    // @param sensor Sensor to be set
    // @param sensorID ID which determines where the sensor is placed
    void setSensor(const Sensor* sensor, u32 sensorID);
    // Gets a sensor
    // @param sensorID ID which determines which sensor to get
    // @return Pointer to retrieved sensor
    const Sensor* getSensor(u32 sensorID) const;
    bool doExplosionAt(const Vec2f& topLeft, const Vec2f& bottomRight);

    // Checks if the actor is on ground
    // @return Whether or not the actor is currently on ground
    inline bool isOnGround()      { return this->output & Flag_OnGround;      }
    // Checks if the actor is colliding with something on the right
    // @return Whether or not the actor is currently colliding with something on the right
    inline bool isCollidedRight() { return this->output & Flag_CollidedRight; }
    // Checks if the actor is colliding with something on the left
    // @return Whether or not the actor is currently colliding with something on the left
    inline bool isCollidedLeft()  { return this->output & Flag_CollidedLeft;  }
    // Checks if the actor is colliding with something
    // @param direction Direction to check collision
    // @return Whether or not the actor is currently colliding with something
    inline bool isCollided(u32 direction) {
        if (direction > 1) return false;
        return this->output & (Flag_CollidedRight << direction);
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

static_assert(sizeof(PhysicsMgr) == 0x14E0, "PhysicsMgr size mismatch");
