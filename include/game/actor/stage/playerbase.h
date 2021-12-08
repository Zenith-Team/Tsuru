#pragma once

#include "game/actor/stage/stageactor.h"
#include "game/playerinput.h"

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

public:
    u8 _27C[0x2C];                        // 27C
    PlayerInput input;                    // 2A8
    u8 _33C[0x1C4];                       // 33C
    PowerupState powerupState;            // 500
    u8 _504[0x4];                         // 504
    ActorPhysicsMgr playerPhysicsMgr;     // 508
    u8 _19E8[0xC0];                       // 19E8
    PhysicsMgr::Sensor sensorID2;         // 1AA8
    PhysicsMgr::Sensor sensorID3;         // 1AB4
    PhysicsMgr::Sensor sensorID0_1;       // 1AC0
    u8 _1ACC[0xEC];                       // 1ACC
    HitboxCollider playerHitboxCollider1; // 1BB8
    HitboxCollider playerHitboxCollider2; // 1CE0
    HitboxCollider playerHitboxCollider3; // 1E08
    HitboxCollider playerHitboxCollider4; // 1F30
    u8 _2058[0x6F8];                      // 2058
};
