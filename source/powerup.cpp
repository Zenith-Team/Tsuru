#include "types.h"

#define TallType_Small 1
#define TallType_Normal 2
#define TallType_Mini 0

ASM_BEGIN

.rodata

PowerupCenterOffsetTable:
    .float 16.0             // Small
    .float 16.0             // Big
    .float 31.0             // Fire
    .float 31.0             // Mini
    .float 6.0              // Propeller
    .float 31.0             // Penguin
    .float 31.0             // Ice
    .float 31.0             // Acorn
    .float 31.0             // PAcorn
    // Begin custom entries
    .float 31.0

PowerupTallTypeTable:
    .long TallType_Small    // Small
    .long TallType_Normal   // Big
    .long TallType_Normal   // Fire
    .long TallType_Mini     // Mini
    .long TallType_Normal   // Propeller
    .long TallType_Normal   // Penguin
    .long TallType_Normal   // Ice
    .long TallType_Normal   // Acorn
    .long TallType_Normal   // PAcorn
    // Begin custom entries 
    .long TallType_Normal   

ARRAY_1016cd68:
    .float 0.0              // Small
    .float -4.0             // Big
    .float -4.0             // Fire
    .float 4.0              // Mini
    .float -5.0             // Propeller
    .float -2.0             // Penguin
    .float -4.0             // Ice
    .float -4.0             // Acorn
    .float -4.0             // PAcorn
    // Begin custom data
    .float -4.0

PowerupBlahTableOffsets:
    .long 1                 // Small
    .long 2                 // Big
    .long 2                 // Fire
    .long 0                 // Mini
    .long 3                 // Propeller
    .long 2                 // Penguin
    .long 2                 // Ice
    .long 2                 // Acorn
    .long 2                 // PAcorn
    // Begin custom data
    .long 2

ARRAY_1016ce20:
    .float -10.0 // Small
    .float 9.0   // Big
    .float 0.0   // Fire
    .float -7.0  // Mini
    .float 6.0   // Propeller
    .float 15.9  // Penguin
    .float 4.0   // Ice
    .float 12.0  // Acorn
    .float 15.9  // PAcorn
    // Begin custom data
    .float 9.0

ARRAY_1016ce44:
    .float -5.0 // Small
    .float 4.0  // Big
    .float 4.0  // Fire
    .float -2.0 // Mini
    .float 1.0  // Propeller
    .float 27.0 // Penguin
    .float 8.0  // Ice
    .float 23.0 // Acorn
    .float 7.9  // PAcorn
    // Begin custom data
    .float 4.0

ARRAY_1016d7f8:
    .float 0.6 // Small
    .float 1.0 // Big
    .float 1.0 // Fire
    .float 0.1 // Mini
    .float 0.6 // Propeller
    .float 0.6 // Penguin
    .float 0.1 // Ice
    .float 0.6 // Acorn
    .float 0.6 // PAcorn
    // Begin custom data
    .float 0.6

.text

.global UseCustomPowerupCenterOffsetTable
UseCustomPowerupCenterOffsetTable:
    lis r11, PowerupCenterOffsetTable@ha
    addi r11, r11, PowerupCenterOffsetTable@l
    
    blr

.global UseCustomPowerupTallTypeTable
UseCustomPowerupTallTypeTable:
    lis r0, PowerupTallTypeTable@h
    ori r0, r0, PowerupTallTypeTable@l
    slwi r12, r4, 2
    lwzx r3, r12, r0
    blr

.global UseCustomArray_1016cd68
UseCustomArray_1016cd68:
    lis r0, ARRAY_1016cd68@h
    ori r0, r0, ARRAY_1016cd68@l
    blr

.global UseCustomArray_1016ce20
UseCustomArray_1016ce20:
    lis r3, ARRAY_1016ce20@ha
    addi r3, r3, ARRAY_1016ce20@l
    blr

.global UseCustomArray_1016ce44
UseCustomArray_1016ce44:
    lis r3, ARRAY_1016ce44@ha
    addi r3, r3, ARRAY_1016ce44@l
    blr

.global UseCustomArray_1016d7f8
UseCustomArray_1016d7f8:
    lis r0, ARRAY_1016d7f8@h
    ori r0, r0, ARRAY_1016d7f8@l
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
