#include "game/actor/stage/player.h"
#include "game/actor/stage/multistateactor.h"
#include "game/actor/actormgr.h"
#include "log.h"

f32 PowerupCenterOffsetTable[PlayerBase::PowerupState::Num] = {
    16.0f,                          // Small
    31.0f,                          // Big
    31.0f,                          // Fire
    6.0f,                           // Mini
    31.0f,                          // Propeller
    31.0f,                          // Penguin
    31.0f,                          // Ice
    31.0f,                          // Acorn
    31.0f,                          // PAcorn
    //* Begin custom entries
    31.0f                           // Hammer Suit
};

PlayerBase::TallType::__type__ PowerupTallTypeTable[PlayerBase::PowerupState::Num] = {
    PlayerBase::TallType::Small,    // Small
    PlayerBase::TallType::Normal,   // Big
    PlayerBase::TallType::Normal,   // Fire
    PlayerBase::TallType::Mini,     // Mini
    PlayerBase::TallType::Normal,   // Propeller
    PlayerBase::TallType::Normal,   // Penguin
    PlayerBase::TallType::Normal,   // Ice
    PlayerBase::TallType::Normal,   // Acorn
    PlayerBase::TallType::Normal,   // PAcorn
    //* Begin custom entries
    PlayerBase::TallType::Normal    // Hammer Suit
};

// YetAnotherTable
f32 ARRAY_1016CD68[PlayerBase::PowerupState::Num] = {
     0.0f,                          // Small
    -4.0f,                          // Big
    -4.0f,                          // Fire
     4.0f,                          // Mini
    -5.0f,                          // Propeller
    -2.0f,                          // Penguin
    -4.0f,                          // Ice
    -4.0f,                          // Acorn
    -4.0f,                          // PAcorn
    //* Begin custom entries
    -4.0f                           // Hammer Suit
};

// BlahTableOffsets
u32 PowerupBlahTableOffsets[PlayerBase::PowerupState::Num] = {
    1,                              // Small
    2,                              // Big
    2,                              // Fire
    0,                              // Mini
    3,                              // Propeller
    2,                              // Penguin
    2,                              // Ice
    2,                              // Acorn
    2,                              // PAcorn
    //* Begin custom entries
    2                               // Hammer Suit
};

f32 ARRAY_1016CE20[PlayerBase::PowerupState::Num] = {
    -10.0f,                         // Small
    9.0f,                           // Big
    0.0f,                           // Fire
    -7.0f,                          // Mini
    6.0f,                           // Propeller
    15.9f,                          // Penguin
    4.0f,                           // Ice
    12.0f,                          // Acorn
    15.9f,                          // PAcorn
    //* Begin custom entries
    0.0f                            // Hammer Suit (Unknown)
};

f32 ARRAY_1016CE44[PlayerBase::PowerupState::Num] = {
    -5.0f,                          // Small
    4.0f,                           // Big
    4.0f,                           // Fire
    -2.0f,                          // Mini
    1.0f,                           // Propeller
    27.0f,                          // Penguin
    8.0f,                           // Ice
    23.0f,                          // Acorn
    7.9f,                           // PAcorn
    //* Begin custom entries
    4.0f                            // Hammer Suit (Unknown)
};

f32 ARRAY_1016D7F8[PlayerBase::PowerupState::Num] = {
    0.6f,                           // Small
    1.0f,                           // Big
    1.0f,                           // Fire
    0.1f,                           // Mini
    0.6f,                           // Propeller
    0.6f,                           // Penguin
    0.1f,                           // Ice
    0.6f,                           // Acorn
    0.6f,                           // PAcorn
    //* Begin custom entries
    1.0f                            // Hammer Suit (Unknown)
};

u32 ARRAY_101750A4[PlayerBase::PowerupState::Num] = {
    1,                              // Small
    2,                              // Big
    2,                              // Fire
    0,                              // Mini
    2,                              // Propeller
    2,                              // Penguin
    2,                              // Ice
    2,                              // Acorn
    2,                              // PAcorn
    //* Begin custom entries
    2                               // Hammer Suit
};

sead::SafeString PowerupSwitchTexAnimArray1[] = {
    "PH_switch",
    "PH_switch",
    "PH_switch",
    "PH_switch",
    "MMH_model_switch",
    
    "PH_switch",
};

sead::SafeString PowerupSwitchTexAnimArray2[] = {
    "PB_switch",
    "PB_switch",
    "PB_switch",
    "PB_switch",
    "MMB_model_switch",

    "PB_switch",
};

sead::SafeString PowerupSwitchTexAnimArray3[] = {
    "PH_switch",
    "PH_switch",
    "PH_switch",
    "PH_switch",
    "MLH_model_switch",

    "PH_switch",
};

sead::SafeString PowerupSwitchTexAnimArray4[] = {
    "PB_switch",
    "PB_switch",
    "PB_switch",
    "PB_switch",
    "MLB_model_switch",

    "PB_switch",
};

extern "C" PlayerBase::TallType::__type__ UseCustomPowerupTallTypeTable(Player*, PlayerBase::PowerupState::__type__ powerupState) {
    return PowerupTallTypeTable[powerupState];
}

extern "C" u32 UseCustomArray_101750A4(PlayerBase::PowerupState::__type__ powerupState) {
    return ARRAY_101750A4[powerupState];
}

extern "C" bool ShouldGiveNewPowerup(Player* _this, PlayerBase::PowerupState::__type__ newPowerupState) {
    PlayerBase::PowerupState::__type__ selfPowerupState = _this->powerupState2;

    switch (newPowerupState) {
        case PlayerBase::PowerupState::Small: // Never downgrade to small
            return false;

        case PlayerBase::PowerupState::Big: // Only become big if we are small or mini
            if (selfPowerupState != PlayerBase::PowerupState::Small && selfPowerupState != PlayerBase::PowerupState::Mini)
                return false;
            return true;
        
        case PlayerBase::PowerupState::Fire:
        case PlayerBase::PowerupState::Mini:
        case PlayerBase::PowerupState::Propeller:
        case PlayerBase::PowerupState::Penguin:
        case PlayerBase::PowerupState::Ice:
            break;
        
        case PlayerBase::PowerupState::Acorn: // Don't downgrade from P-Acorn
            if (selfPowerupState == PlayerBase::PowerupState::PAcorn)
                return false;
            break;

        case PlayerBase::PowerupState::PAcorn:
            break;

        //* Custom powerup states
        case PlayerBase::PowerupState::Hammer:
            break;

        default:
            return false;
    }

    if (selfPowerupState == newPowerupState)
        return false;

    return true;
}

extern "C" const char* PowerupChangeSoundEffect(void* _this) {
    PlayerBase::PowerupState::__type__ v1 = *(PlayerBase::PowerupState::__type__*)(((u32)_this) + 0x4);
    PlayerBase::PowerupState::__type__ v2 = *(PlayerBase::PowerupState::__type__*)(((u32)_this) + 0x24);
    
    if (v2 < PlayerBase::PowerupState::Propeller) {
        if (v2 == PlayerBase::PowerupState::Small)
            return "SE_PLY_CHANGE_SMALL";
        if (v2 > PlayerBase::PowerupState::Fire)
            return "SE_PLY_CHANGE_MAME";
    } else if (v2 > PlayerBase::PowerupState::Propeller) {
        if (v2 == PlayerBase::PowerupState::Penguin)
            return "SE_PLY_CHANGE_MAME";
        if (v2 > PlayerBase::PowerupState::Acorn)
            return "SE_PLY_CHANGE_SMALL";

        if (v1 == PlayerBase::PowerupState::Fire)
            return "SE_PLY_CHANGE_BIG";
        if (v1 < PlayerBase::PowerupState::Propeller)
            return "SE_PLY_CHANGE_SMALL";
        if (v1 < (PlayerBase::PowerupState::Big | PlayerBase::PowerupState::PAcorn)) {
            static const char* const strArr[] = {
                "SE_PLY_CHANGE_PRPL",   // Propeller
                "SE_PLY_CHANGE_PNGN",   // Penguin
                "SE_PLY_CHANGE_BIG",    // Ice Flower
                "SE_PLY_CHANGE_MSSB",   // Acorn
                "SE_PLY_CHANGE_P_MSSB", // P-Acorn
            };

            return strArr[v1 - PlayerBase::PowerupState::Propeller];
        }

        //* Custom powerups
        if (v1 > PlayerBase::PowerupState::PAcorn && v1 < PlayerBase::PowerupState::Num)
            return "SE_PLY_CHANGE_BIG";

        return "SE_PLY_CHANGE_SMALL";
    }

    if (v1 == PlayerBase::PowerupState::Propeller)
        return "SE_PLY_CHANGE_PRPL";
    if (v1 == PlayerBase::PowerupState::Penguin)
        return "SE_PLY_CHANGE_PNGN";
    if (v1 == PlayerBase::PowerupState::Acorn)
        return "SE_PLY_CHANGE_MSSB";
    if (v1 == PlayerBase::PowerupState::PAcorn)
        return "SE_PLY_CHANGE_P_MSSB";

    //* Custom powerups
    if (v1 > PlayerBase::PowerupState::PAcorn && v1 < PlayerBase::PowerupState::Num)
        return "SE_PLY_CHANGE_BIG";

    return "SE_PLY_CHANGE_BIG";
}

extern "C" bool CheckProjectileSpawnLimits(Player* _this, PlayerBase::PowerupState::__type__ powerup) {
    switch (powerup) {
        case PlayerBase::PowerupState::Hammer: {
            u32 myHammerCount = 0;

            for (Actor** i = ActorMgr::instance()->actors.start.buffer; i < ActorMgr::instance()->actors.end.buffer; i++) {
                if ((*i) != nullptr && (*i)->getProfileID() == ProfileID::Hammer) {
                    u32 parentActorID = *(u32*)(((u32)(*i))+0x2E60); // Hammer::parentActorID
                    Actor* parent = ActorMgr::instance()->actors.findActorByID(parentActorID);

                    if (parent == _this)
                        myHammerCount++;
                }
            }

            if (myHammerCount >= 2)
                return false;
        }

        default: return true;
    }
}

extern "C" void* HammerShootInit(StageActor* _this) {
    u32 parentActorID = *(u32*)(((u32)_this)+0x2E60); // Hammer::parentActorID
    StageActor* parent = static_cast<StageActor*>(ActorMgr::instance()->actors.findActorByID(parentActorID));

    if (parentActorID != 0 && parent && parent->type == StageActor::Type::Player) {
        *(bool*)(((u32)_this)+0x2E2C) = true; // Hammer::readyToThrow
        _this->settings1 = parent->direction == Direction::Left;
    }

    return _this;
}

extern "C" StateBase* HammerStateCheck(MultiStateActor* actor) {
    if (actor->type == StageActor::Type::Player)
        return &StateBase::sNullState;

    return actor->states.manager.getCurrentState();
}

extern "C" void HammerShootState(StateMgr* stateMgr, StateBase* state, StageActor* hammer) {
    u32 parentActorID = *(u32*)(((u32)hammer)+0x2E60); // Hammer::parentActorID
    StageActor* parent = static_cast<StageActor*>(ActorMgr::instance()->actors.findActorByID(parentActorID));

    if (parentActorID != 0 && parent && parent->type == StageActor::Type::Player) {
        YoshiEatData* eatData = *(YoshiEatData**)(((u32)hammer)+0x17E0); // Hammer::yoshiEatData
        eatData->vf4C(parent);
    } else {
        stateMgr->changeState(state);
    }
}

ASM_BEGIN

.include "macros.S"

.text

.global HammerSetParentID
HammerSetParentID:
    lwz r3, 0x8(r30)
    stw r3, 0x2E60(r31)
    mr  r3, r31

    b __ct__10StateActorFPC14ActorBuildInfo

.global HammerStateCheckASM
HammerStateCheckASM:
    mr r3, r31
    b HammerStateCheck

.global HammerShootStateASM
HammerShootStateASM:
    mr r5, r30
    SafeBranch HammerShootState

    blr

.global AnotherProjectilePowerupCheck
AnotherProjectilePowerupCheck:
    cmpwi r8, 2
    beqlr

    //* ------ Begin extra types ------

    cmpwi r8, 9
    beqlr

    //* ------ End extra types ------

    blr

.global AllowThrowingProjectile
AllowThrowingProjectile:
    // If comparison is true we will continue to throw

    // Ice flower
    cmpwi r0, 6
    beqlr

    //* ------ Begin extra types ------

    // Hammer Suit
    cmpwi r0, 9
    beqlr

    //* ------ End extra types ------

    blr

.global ProjectileExtraTypes
ProjectileExtraTypes:
    // If comparison is true we will throw a fireball (or the hijacked equivalent)

    //* Fire Flower
    cmpwi r0, 2
    beqlr

    //* ------ Begin extra types ------

    // Hammer Suit
    cmpwi r0, 9
    beqlr

    //* ------ End extra types ------

    blr

.global ProjectileSelectSFX
ProjectileSelectSFX:
    // r0 = powerupState
    // r4 = const char* sfxName
    mr r7, r0

    SaveVolatileRegisters
    
    //* Fire Flower
    cmpwi r7, 2
    beq ProjectileSelectSFX_Go

    //* ------ Begin extra types ------

    // Hammer Suit
    cmpwi r7, 9
    beq ProjectileSelectSFX_None

    //* ------ End extra types ------

ProjectileSelectSFX_Go:
    bl playSfx__6PlayerFPCcUi

ProjectileSelectSFX_None:
    RestoreVolatileRegisters

    blr

.global ShouldThrowProjectile
ShouldThrowProjectile: // Custom version of Player::shouldThrowProjectile
    lis       r12, sInstance__18ActorGlobalsHolder@ha
    lwz       r0, 0x500(r3)

    cmpwi     r0, 2
    beq       ShouldThrowProjectileIsFire

    //* ------ Begin extra types ------

    // Hammer Suit
    cmpwi     r0, 9
    beq       ShouldThrowProjectileIsFire // should shoot

    //* ------ End extra types ------

    b         ShouldThrowProjectileIsNotFire // should not shoot

.global ShouldThrowProjectile_2
ShouldThrowProjectile_2:
    lis       r12, sInstance__18ActorGlobalsHolder@ha
    lwz       r0, 0x500(r3)

    cmpwi     r0, 2
    beq       ShouldThrowProjectile_2IsFire

    //* ------ Begin extra types ------

    // Hammer Suit
    cmpwi     r0, 9
    beq       ShouldThrowProjectile_2IsFire // should shoot

    //* ------ End extra types ------

    b         ShouldThrowProjectile_2NotFire // should not shoot

ShouldThrowProjectileIsFire:
    mr        r10, r0
    SaveVolatileRegisters
    mr        r4, r10
    bl        CheckProjectileSpawnLimits
    cmpwi     r3, 0
    beq       DontShoot
    RestoreVolatileRegisters

    cmpwi     r4, 0
    bne       ShouldThrowProjectileReturn1
    lbz       r10, 0x54(r3)
    lwz       r12, sInstance__18ActorGlobalsHolder@l(r12)
    extsb     r10, r10
    cmplwi    r10, 4
    addi      r11, r12, 0x64
    bge       ShouldThrowProjectilePreReturn1
    slwi      r12, r10, 3
    add       r11, r11, r12
ShouldThrowProjectilePreReturn1:
    lwz       r0, 4(r11)
    cmpwi     r0, 2
    blt       ShouldThrowProjectileReturn1
ShouldThrowProjectileReturn0:
    li        r3, 0
    blr
ShouldThrowProjectileIsNotFire:
    cmpwi     r0, 5
    beq       ShouldThrowProjectileIsNotIce
    cmpwi     r0, 6
    bne       ShouldThrowProjectileReturn0
ShouldThrowProjectileIsNotIce:
    cmpwi     r4, 0
    bne       ShouldThrowProjectileReturn1
    lbz       r0, 0x54(r3)
    lwz       r12, sInstance__18ActorGlobalsHolder@l(r11)
    extsb     r0, r0
    cmplwi    r0, 4
    addi      r12, r12, 0x84
    bge       ShouldThrowProjectilePreReturn0
    slwi      r0, r0, 3
    add       r12, r12, r0
ShouldThrowProjectilePreReturn0:
    lwz       r11, 4(r12)
    cmpwi     r11, 2
    bge       ShouldThrowProjectileReturn0
ShouldThrowProjectileReturn1:
    li        r3, 1
    blr

ShouldThrowProjectile_2IsFire:
    SaveVolatileRegisters
    mr        r4, r0
    bl        CheckProjectileSpawnLimits
    cmpwi     r3, 0
    beq       DontShoot
    RestoreVolatileRegisters

    lbz       r11, 0x54(r3)
    lwz       r12, sInstance__18ActorGlobalsHolder@l(r12)
    extsb     r11, r11
    cmplwi    r11, 4
    addi      r12, r12, 0x64
    bge       ShouldThrowProjectile_2PreReturn1
    slwi      r0, r11, 3
    add       r12, r12, r0
ShouldThrowProjectile_2PreReturn1:
    lwz       r11, 0(r12)
    cmpwi     r11, 6
    blt       ShouldThrowProjectileReturn1
ShouldThrowProjectile_2NotFire:
    cmpwi     r0, 5
    beq       ShouldThrowProjectile_2NotIce
    cmpwi     r0, 6
    bne       ShouldThrowProjectileReturn0
ShouldThrowProjectile_2NotIce:
    lbz       r0, 0x54(r3)
    lwz       r12, sInstance__18ActorGlobalsHolder@l(r12)
    extsb     r0, r0
    cmplwi    r0, 4
    addi      r11, r12, 0x84
    bge       ShouldThrowProjectile_2PreReturn0
    slwi      r12, r0, 3
    add       r11, r11, r12
ShouldThrowProjectile_2PreReturn0:
    lwz       r0, 0(r11)
    cmpwi     r0, 6
    bge       ShouldThrowProjectileReturn0

DontShoot:
    RestoreVolatileRegisters
    li        r3, 0
    blr

.global ProjectileProfileIDs
ProjectileProfileIDs:
    // Load powerup state
    lwz r3, 0x500(r30)

    //* ------ Begin extra types ------

    // Hammer Suit
    cmpwi r3, 9
    li r3, 758 // hammer
    beq SpawnProjectile

    //* ------ End extra types ------

    // Otherwise fire
    li r3, 0x1DC
SpawnProjectile:
    b get__7ProfileSFUi

.global ProjectileParentID
ProjectileParentID:
    lwz r0, 0x4(r30)
    stw r0, 0x44(r1)
    lwz r0, 0x500(r30) // replaced instruction
    blr

.global UseCustomPowerupCenterOffsetTable
UseCustomPowerupCenterOffsetTable:
    lis r11, PowerupCenterOffsetTable@ha
    addi r11, r11, PowerupCenterOffsetTable@l
    subi r11, r11, 0x4

    blr

.global UseCustomArray_1016CD68
UseCustomArray_1016CD68:
    lis r0, ARRAY_1016CD68@h
    ori r0, r0, ARRAY_1016CD68@l
    blr

.global UseCustomArray_1016CE20
UseCustomArray_1016CE20:
    lis r3, ARRAY_1016CE20@ha
    addi r3, r3, ARRAY_1016CE20@l
    blr

.global UseCustomArray_1016CE44
UseCustomArray_1016CE44:
    lis r3, ARRAY_1016CE44@ha
    addi r3, r3, ARRAY_1016CE44@l
    blr

.global UseCustomArray_1016D7F8
UseCustomArray_1016D7F8:
    lis r0, ARRAY_1016D7F8@h
    ori r0, r0, ARRAY_1016D7F8@l
    blr

.global UseCustomBlahTableOffsets
UseCustomBlahTableOffsets:
    lis r0, PowerupBlahTableOffsets@h
    ori r0, r0, PowerupBlahTableOffsets@l
    b Player_vfA5C_continue

.global UseCustomPowerupSwitchTexAnimArray1
UseCustomPowerupSwitchTexAnimArray1:
    lis r9, PowerupSwitchTexAnimArray1@ha
    addi r9, r9, PowerupSwitchTexAnimArray1@l
    blr

.global UseCustomPowerupSwitchTexAnimArray2
UseCustomPowerupSwitchTexAnimArray2:
    lis r10, PowerupSwitchTexAnimArray2@ha
    addi r10, r10, PowerupSwitchTexAnimArray2@l
    blr

.global UseCustomPowerupSwitchTexAnimArray3
UseCustomPowerupSwitchTexAnimArray3:
    lis r9, PowerupSwitchTexAnimArray3@ha
    addi r9, r9, PowerupSwitchTexAnimArray3@l
    blr

.global UseCustomPowerupSwitchTexAnimArray4
UseCustomPowerupSwitchTexAnimArray4:
    lis r10, PowerupSwitchTexAnimArray4@ha
    addi r10, r10, PowerupSwitchTexAnimArray4@l
    blr

ASM_END
