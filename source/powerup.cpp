#include "game/actor/stage/player.h"

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
    // Begin custom entries
    31.0f
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
    // Begin custom entries
    PlayerBase::TallType::Normal
};

// YetAnotherTable
f32 ARRAY_1016CD68[] = {
     0.0f,                           // Small
    -4.0f,                           // Big
    -4.0f,                           // Fire
     4.0f,                           // Mini
    -5.0f,                           // Propeller
    -2.0f,                           // Penguin
    -4.0f,                           // Ice
    -4.0f,                           // Acorn
    -4.0f,                           // PAcorn
    // Begin custom data
    -4.0f
};

// BlahTableOffsets
u32 PowerupBlahTableOffsets[] = {
    1,                               // Small
    2,                               // Big
    2,                               // Fire
    0,                               // Mini
    3,                               // Propeller
    2,                               // Penguin
    2,                               // Ice
    2,                               // Acorn
    2,                               // PAcorn
    // Begin custom data
    2
};

f32 ARRAY_1016CE20[] = {
    -10.0f,                          // Small
    9.0f,                            // Big
    0.0f,                            // Fire
    -7.0f,                           // Mini
    6.0f,                            // Propeller
    15.9f,                           // Penguin
    4.0f,                            // Ice
    12.0f,                           // Acorn
    15.9f,                           // PAcorn
    // Begin custom data
    9.0f
};

f32 ARRAY_1016CE44[] = {
    -5.0f,                           // Small
    4.0f,                            // Big
    4.0f,                            // Fire
    -2.0f,                           // Mini
    1.0f,                            // Propeller
    27.0f,                           // Penguin
    8.0f,                            // Ice
    23.0f,                           // Acorn
    7.9f,                            // PAcorn
    // Begin custom data
    4.0f
};

f32 ARRAY_1016D7F8[] = {
    0.6f,                            // Small
    1.0f,                            // Big
    1.0f,                            // Fire
    0.1f,                            // Mini
    0.6f,                            // Propeller
    0.6f,                            // Penguin
    0.1f,                            // Ice
    0.6f,                            // Acorn
    0.6f,                            // PAcorn
    // Begin custom data
    0.6f
};

extern "C" PlayerBase::TallType::__type__ UseCustomPowerupTallTypeTable(Player*, PlayerBase::PowerupState::__type__ powerupState) {
    return PowerupTallTypeTable[powerupState];
}

ASM_BEGIN

.text

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
    extrwi.   r6, r11, 1,27
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
    extrwi.   r10, r9, 1,28
    beq       LAB_292EAF8
    li        r0, 0xB
    b         LAB_292EB34
LAB_292EAF8:
    lwz       r6, 0x494(r3)
    extrwi.   r7, r6, 1,1
    beq       LAB_292EB0C
    li        r0, 0xC
    b         LAB_292EB34
LAB_292EB0C:
    lwz       r9, 0x498(r3)
    extrwi.   r11, r9, 1,11
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
