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

public:
    u8 _27C[0x2A8 - 0x27C];
    PlayerInput input;
    u8 _33C[0x500 - 0x33C];
    PowerupState powerupState;
    u8 _504[0x508 - 0x504];
    ActorPhysicsMgr playerPhysicsMgr;
    u8 _19E8[0x1AA8 - 0x19E8];
    PhysicsMgr::Sensor sensorID2;
    PhysicsMgr::Sensor sensorID3;
    PhysicsMgr::Sensor sensorID0_1;
    u8 _1ACC[0x1BB8 - 0x1ACC];
    HitboxCollider playerHitboxCollider1;
    HitboxCollider playerHitboxCollider2;
    HitboxCollider playerHitboxCollider3;
    HitboxCollider playerHitboxCollider4;
    u8 _2058[0x2750 - 0x2058];
};
