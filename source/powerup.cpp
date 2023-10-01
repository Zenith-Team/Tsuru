#include "game/actor/stage/player.h"
#include "game/actor/stage/multistateactor.h"
#include "game/actor/actormgr.h"
#include "game/graphics/model/charactermodel.h"
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

// Sound related
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

PlayerModel::PowerupModel::__type__ PlayerModelPowerupTable[PlayerBase::PowerupState::Num] = {
    PlayerModel::PowerupModel::Small,       // Small
    PlayerModel::PowerupModel::Normal,      // Big
    PlayerModel::PowerupModel::Normal,      // Fire
    PlayerModel::PowerupModel::Small,       // Mini
    PlayerModel::PowerupModel::Propeller,   // Propeller
    PlayerModel::PowerupModel::Penguin,     // Penguin
    PlayerModel::PowerupModel::Normal,      // Ice
    PlayerModel::PowerupModel::Squirrel,    // Acorn
    PlayerModel::PowerupModel::Squirrel,    // PAcorn
    //* Begin custom entries
    PlayerModel::PowerupModel::Normal       // Hammer Suit
};

// Array of Vec2 but using floats because GHS will literally choke and not properly init the tables...
f32 PowerupYoshiOffsetTable1[PlayerBase::PowerupState::Num * 2] = {
    -2.5f, -7.0f, // Small
    -9.2f, -6.5f, // Big
    -9.2f, -6.5f, // Fire
     1.0f, -6.5f, // Mini
    -9.2f, -6.5f, // Propeller
    -5.5f, -6.0f, // Penguin
    -9.2f, -6.5f, // Ice
    -9.2f, -6.5f, // Acorn
    -9.2f, -6.5f, // PAcorn
    //* Begin custom entries
    -9.2f, -6.5f  // Hammer Suit
};

// Array of Vec2 but using floats because GHS will literally choke and not properly init the tables...
f32 PowerupYoshiOffsetTable2[PlayerBase::PowerupState::Num * 2] = {
    -3.0f, -7.0f, // Small
    -9.7f, -6.0f, // Big
    -9.7f, -6.0f, // Fire
     1.5f, -6.5f, // Mini
    -9.7f, -6.0f, // Propeller
    -9.7f, -6.0f, // Penguin
    -9.7f, -6.0f, // Ice
    -9.7f, -6.0f, // Acorn
    -9.7f, -6.0f, // PAcorn
    //* Begin custom entries
    -9.7f, -6.0f  // Hammer Suit
};

// Array of Vec2 but using floats because GHS will literally choke and not properly init the tables...
f32 PowerupYoshiOffsetTable3[PlayerBase::PowerupState::Num * 2] = {
    -0.5f, -7.0f, // Small
    -2.0f, -6.0f, // Big
    -2.0f, -6.0f, // Fire
     3.0f, -7.0f, // Mini
    -2.0f, -6.0f, // Propeller
    -2.0f, -6.0f, // Penguin
    -2.0f, -6.0f, // Ice
    -2.0f, -6.0f, // Acorn
    -2.0f, -6.0f, // PAcorn
    //* Begin custom entries
    -2.0f, -6.0f, // Hammer Suit
};

// Array of Vec2 but using floats because GHS will literally choke and not properly init the tables...
f32 PowerupYoshiOffsetTable4[PlayerBase::PowerupState::Num * 2] = {
    -2.5f, -7.0f, // Small
    -9.0f, -6.5f, // Big
    -9.0f, -6.5f, // Fire
     1.0f, -6.5f, // Mini
    -9.0f, -6.5f, // Propeller
    -5.5f, -6.0f, // Penguin
    -9.0f, -6.5f, // Ice
    -9.0f, -6.5f, // Acorn
    -9.0f, -6.5f, // PAcorn
    //* Begin custom entries
    -9.0f, -6.5f, // Hammer Suit
};

sead::SafeString PowerupSwitchTexAnimArray1[PlayerModel::PowerupModel::NumOriginal] = {
    "PH_switch",
    "PH_switch",
    "PH_switch",
    "PH_switch",
    "MMH_model_switch"
};

sead::SafeString PowerupSwitchTexAnimArray2[PlayerModel::PowerupModel::NumOriginal] = {
    "PB_switch",
    "PB_switch",
    "PB_switch",
    "PB_switch",
    "MMB_model_switch"
};

sead::SafeString PowerupSwitchTexAnimArray3[PlayerModel::PowerupModel::NumOriginal] = {
    "PH_switch",
    "PH_switch",
    "PH_switch",
    "PH_switch",
    "MLH_model_switch"
};

sead::SafeString PowerupSwitchTexAnimArray4[PlayerModel::PowerupModel::NumOriginal] = {
    "PB_switch",
    "PB_switch",
    "PB_switch",
    "PB_switch",
    "MLB_model_switch"
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
        if (v1 < PlayerBase::PowerupState::NumOriginal) {
            static const char* const strArr[] = {
                "SE_PLY_CHANGE_PRPL",   // Propeller
                "SE_PLY_CHANGE_PNGN",   // Penguin
                "SE_PLY_CHANGE_BIG",    // Ice Flower
                "SE_PLY_CHANGE_MSSB",   // Acorn
                "SE_PLY_CHANGE_P_MSSB", // PAcorn
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

extern "C" bool PlayerThrowProjectile(PlayerBase::PowerupState::__type__ powerup, ActorBuildInfo* projectile, Player* player) {
    if (powerup == PlayerBase::PowerupState::Hammer) {
        projectile->profile = Profile::get(ProfileID::Hammer);
        projectile->settings1 = player->_2A00; // Spawn direction
        return true;
    }

    return false;
}

extern "C" void* HammerShootInit(StageActor* _this) {
    u32 parentActorID = *(u32*)(((u32)_this)+0x2E60); // Hammer::parentActorID
    StageActor* parent = static_cast<StageActor*>(ActorMgr::instance()->actors.findActorByID(parentActorID));

    if (parentActorID != 0 && parent && parent->type == StageActor::Type::Player) {
        *(bool*)(((u32)_this)+0x2E2C) = true; // Hammer::readyToThrow
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
        u32 playerDir = parent->direction;
        parent->direction = hammer->settings1;
        eatData->vf4C(parent);
        parent->direction = playerDir;
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

.global ThrowProjectileASM
ThrowProjectileASM:
    cmpwi r0, 0x5 # Penguin
    beq ThrowProjectileASM_Ice
    cmpwi r0, 0x6 # Ice
    beq ThrowProjectileASM_Ice

    mr r3, r0
    addi r4, r1, 0x3C
    mr r5, r30
    SaveVolatileRegisters
    bl PlayerThrowProjectile
    cmpwi r3, 0
    beq ThrowProjectileASM_return
    RestoreVolatileRegisters
    b Player_throwProjectile_continue

ThrowProjectileASM_Ice:
    lis   r3, Player_throwProjectile_throwIce@ha
    addi  r3, r3, Player_throwProjectile_throwIce@l
    mtctr r3
    bctr

ThrowProjectileASM_return:
    RestoreVolatileRegisters
    b Player_throwProjectile_return

.global AllowThrowingProjectile
AllowThrowingProjectile:
    // If comparison is true we will continue to throw
    // Fire and Penguin is already checked

    // Ice flower
    cmpwi r0, 6
    beqlr

    //* ------ Begin extra types ------

    // Hammer Suit
    cmpwi r0, 9
    beqlr

    //* ------ End extra types ------

    blr

.global HasLessThan6OldProjectiles
HasLessThan6OldProjectiles:
    // Fire flower
    cmpwi r0, 2
    beq HasLessThan6OldProjectiles_Continue

    //* ------ Begin extra types ------

    // Hammer Suit
    cmpwi r0, 9
    beq HasLessThan6OldProjectiles_ReturnTrue

    //* ------ End extra types ------

HasLessThan6OldProjectiles_Continue:
    lis   r3, Player_hasLessThan6OldProjectiles_continue@ha
    addi  r3, r3, Player_hasLessThan6OldProjectiles_continue@l
    mtctr r3
    bctr

HasLessThan6OldProjectiles_ReturnTrue:
    li r3, 1
    blr

.global HasLessThan2NewProjectiles
HasLessThan2NewProjectiles:
    // Fire flower
    cmpwi r0, 2
    beq HasLessThan2NewProjectiles_Continue

    //* ------ Begin extra types ------

    // Hammer Suit
    cmpwi r0, 9
    beq HasLessThan2NewProjectiles_CheckProjectileLimit

    //* ------ End extra types ------

HasLessThan2NewProjectiles_Continue:
    lis   r3, Player_hasLessThan2NewProjectiles_continue@ha
    addi  r3, r3, Player_hasLessThan2NewProjectiles_continue@l
    mtctr r3
    bctr

HasLessThan2NewProjectiles_CheckProjectileLimit:
    // r3 is already Player*
    mr r4, r0
    b CheckProjectileSpawnLimits

.global ProjectileParentID
ProjectileParentID:
    lwz r0, 0x4(r30)
    stw r0, 0x44(r1)
    lwz r0, 0x500(r30) // replaced instruction
    blr

.global UseCustomPowerupCenterOffsetTable
UseCustomPowerupCenterOffsetTable:
    lis r9, PowerupCenterOffsetTable@ha
    addi r9, r9, PowerupCenterOffsetTable@l

    lfsx f12, r12, r9

    blr

.global UseCustomBlahTableOffsets
UseCustomBlahTableOffsets:
    lis r0, PowerupBlahTableOffsets@h
    ori r0, r0, PowerupBlahTableOffsets@l
    b Player_vfA5C_continue

.global UseCustomArray_1016CD68
UseCustomArray_1016CD68:
    lis r0, ARRAY_1016CD68@h
    ori r0, r0, ARRAY_1016CD68@l
    blr

.global UseCustomPowerupYoshiOffset1
UseCustomPowerupYoshiOffset1:
    lis r11, PowerupYoshiOffsetTable1@ha
    addi r11, r11, PowerupYoshiOffsetTable1@l
    b UseCustomPowerupYoshiOffset1_continue

.global UseCustomPowerupYoshiOffset2
UseCustomPowerupYoshiOffset2:
    lis r12, PowerupYoshiOffsetTable2@ha
    addi r12, r12, PowerupYoshiOffsetTable2@l
    b UseCustomPowerupYoshiOffset2_continue

.global UseCustomPowerupYoshiOffset3
UseCustomPowerupYoshiOffset3:
    lis r12, PowerupYoshiOffsetTable3@ha
    addi r12, r12, PowerupYoshiOffsetTable3@l
    b UseCustomPowerupYoshiOffset3_continue

.global UseCustomPowerupYoshiOffset4
UseCustomPowerupYoshiOffset4:
    lis r12, PowerupYoshiOffsetTable4@ha
    addi r12, r12, PowerupYoshiOffsetTable4@l
    b UseCustomPowerupYoshiOffset4_continue

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

.global UseCustomPowerupModelTable
UseCustomPowerupModelTable:
    addis r12, r11, PlayerModelPowerupTable@ha
    lwz r4, PlayerModelPowerupTable@l(r12)
    blr

ASM_END
