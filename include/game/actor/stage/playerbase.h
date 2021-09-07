#pragma once

#include <game/actor/stage/stageactor.h>
#include <game/playerinput.h>

// TODO: finish this

class PlayerBase : public StageActor { // Size: 0x2750
public:
    enum PowerupState {
        PowerupState_Small      = 0,
        PowerupState_Big        = 1,
        PowerupState_Fire       = 2,
        PowerupState_Mini       = 3,
        PowerupState_Propeller  = 4,
        PowerupState_Penguin    = 5,
        PowerupState_Ice        = 6,
        PowerupState_Acorn      = 7,
        PowerupState_PAcorn     = 8
    };

    u8 _27C[0x2C];                        // _27C
    PlayerInput input;                    // _2A8
    u8 _33C[0x1C4];                       // _33C
    PowerupState powerupState;            // _500
    u8 _504[0x4];                         // _504
    ActorPhysicsMgr playerPhysicsMgr;     // _508
    u8 _19E8[0xC0];                       // _19E8
    PhysicsMgr::Sensor sensorID2;         // _1AA8
    PhysicsMgr::Sensor sensorID3;         // _1AB4
    PhysicsMgr::Sensor sensorID0_1;       // _1AC0
    u8 _1ACC[0xEC];                       // _1ACC
    HitboxCollider playerHitboxCollider1; // _1BB8
    HitboxCollider playerHitboxCollider2; // _1CE0
    HitboxCollider playerHitboxCollider3; // _1E08
    HitboxCollider playerHitboxCollider4; // _1F30
    u8 _2058[0x6F8];                      // _2058
};
