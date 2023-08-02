#include "game/actor/stage/player.h"
#include "game/actor/actormgr.h"

f32 PowerupCenterOffsetTable[] = {
    16.0f,                          // Small
    16.0f,                          // Big
    31.0f,                          // Fire
    31.0f,                          // Mini
    6.0f,                           // Propeller
    31.0f,                          // Penguin
    31.0f,                          // Ice
    31.0f,                          // Acorn
    31.0f,                          // PAcorn
    //* Begin custom entries
    31.0f                           // Hammer Suit
};

PlayerBase::TallType::__type__ PowerupTallTypeTable[] = {
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
f32 ARRAY_1016CD68[] = {
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
u32 PowerupBlahTableOffsets[] = {
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

f32 ARRAY_1016CE20[] = {
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
    9.0f                            // Hammer Suit
};

f32 ARRAY_1016CE44[] = {
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
    4.0f                            // Hammer Suit
};

f32 ARRAY_1016D7F8[] = {
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
    0.6f                            // Hammer Suit
};

extern "C" PlayerBase::TallType::__type__ UseCustomPowerupTallTypeTable(Player*, PlayerBase::PowerupState::__type__ powerupState) {
    return PowerupTallTypeTable[powerupState];
}

extern "C" bool ShouldKeepNewPowerup(Player* _this, PlayerBase::PowerupState::__type__ newPowerupState) {
    PlayerBase::PowerupState::__type__ selfPowerupState = _this->powerupState2;

    switch (newPowerupState) {
        case PlayerBase::PowerupState::Small: // Never downgrade to small
            return false;

        case PlayerBase::PowerupState::Big: // Only become big if we are small or mini
            if (selfPowerupState != PlayerBase::PowerupState::Small && selfPowerupState != PlayerBase::PowerupState::Mini)
                return false;
            else
                return true;
        
        case PlayerBase::PowerupState::Fire:
        case PlayerBase::PowerupState::Mini:
        case PlayerBase::PowerupState::Propeller:
        case PlayerBase::PowerupState::Penguin:
        case PlayerBase::PowerupState::Ice:
        case PlayerBase::PowerupState::PAcorn:
            return true;
        
        case PlayerBase::PowerupState::Acorn: // Don't downgrade from P-Acorn
            if (selfPowerupState == PlayerBase::PowerupState::PAcorn)
                return false;
            else
                return true;
        
        // Custom powerup states
        case PlayerBase::PowerupState::PAcorn+1:
            return true;

        default:
            return false;
    }
}

#include "log.h"
extern "C" void* HammerShootInit(StageActor* _this) {
    u32 parentActorID = *(u32*)(((u32)_this)+0x2E60); // Hammer::parentActorID
    StageActor* parent = static_cast<StageActor*>(ActorMgr::instance()->actors.findActorByID(parentActorID));

    if (parentActorID != 0 && parent && parent->type == StageActor::Type::Player) {
        *(bool*)(((u32)_this)+0x2E2C) = true; // Hammer::readyToThrow
        _this->settings1 = parent->direction == Direction::Left;
    }

    return _this;
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
    lis       r11, sInstance__18ActorGlobalsHolder@ha
    lwz       r0, 0x500(r3)

    cmpwi     r0, 2
    beq       ShouldThrowProjectileIsFire

    //* ------ Begin extra types ------

    cmpwi     r0, 9
    bne       ShouldThrowProjectileIsNotFire

    //* ------ End extra types ------

.global ShouldThrowProjectile_2
ShouldThrowProjectile_2:
    lis       r12, sInstance__18ActorGlobalsHolder@ha
    lwz       r0, 0x500(r3)

    cmpwi     r0, 2
    beq       ShouldThrowProjectile_2IsFire

    //* ------ Begin extra types ------

    cmpwi     r0, 9
    bne       ShouldThrowProjectile_2NotFire

    //* ------ End extra types ------

ShouldThrowProjectileIsFire:
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
UseCustomBlahTableOffsets: // Custom version of Player::vfA5C
    lwz       r7, 0x2750(r3)
    lwz       r12, 0x500(r3)
    lis       r0, PowerupBlahTableOffsets@h
    lwz       r10, 0xC4(r7)
    slwi      r11, r12, 2
    ori       r0, r0, PowerupBlahTableOffsets@l
    clrlwi.   r8, r10, 31
    lwzx      r0, r11, r0
    beq       LAB_292EAB8
    cmplwi    r12, 0
    beq       LAB_292EAA8
    cmplwi    r12, 3
    bne       LAB_292EAB0
    li        r0, 4
    b         LAB_292EB34
LAB_292EAA8:
    li        r0, 5
    b         LAB_292EB34
LAB_292EAB0:
    li        r0, 6
    b         LAB_292EB34
LAB_292EAB8:
    lwz       r11, 0xC4(r7)
    extrwi.   r6, r11, 1, 27
    beq       LAB_292EAE4
    cmplwi    r12, 0
    beq       LAB_292EADC
    cmplwi    r12, 3
    beq       LAB_292EB34
    li        r0, 8
    b         LAB_292EB34
LAB_292EADC:
    li        r0, 7
    b         LAB_292EB34
LAB_292EAE4:
    lwz       r9, 0x49C(r3)
    extrwi.   r10, r9, 1, 28
    beq       LAB_292EAF8
    li        r0, 0xB
    b         LAB_292EB34
LAB_292EAF8:
    lwz       r6, 0x494(r3)
    extrwi.   r7, r6, 1, 1
    beq       LAB_292EB0C
    li        r0, 0xC
    b         LAB_292EB34
LAB_292EB0C:
    lwz       r9, 0x498(r3)
    extrwi.   r11, r9, 1, 11
    beq       LAB_292EB34
    cmplwi    r12, 0
    beq       LAB_292EB30
    cmplwi    r12, 3
    beq       LAB_292EB34
    li        r0, 0xA
    b         LAB_292EB34
LAB_292EB30:
    li        r0, 9
LAB_292EB34:
    mr        r3, r0
    blr

ASM_END
