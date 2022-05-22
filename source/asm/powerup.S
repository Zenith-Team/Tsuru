.rodata

.set TallType_Mini,   0
.set TallType_Small,  1
.set TallType_Normal, 2

#? AsdfTable from NSMBW
#* Index corresponds to PowerupState
PowerupTallTypeTable:
    .long TallType_Small    # Small
    .long TallType_Normal   # Big
    .long TallType_Normal   # Fire
    .long TallType_Mini     # Mini
    .long TallType_Normal   # Propeller
    .long TallType_Normal   # Penguin
    .long TallType_Normal   # Ice
    .long TallType_Normal   # Acorn
    .long TallType_Normal   # PAcorn
    # Begin custom data
    .long TallType_Normal   # Kamek hat

#* Index corresponds to TallType
PowerupSensorSizeTable:
    .float 4.0
    .float 8.0
    .float 16.0
    # Begin custom data

#? BlahTableOffsets from NSMBW
# TODO: What does this do?
#* Index corresponds to PowerupState
ARRAY_1016d7cc:
    .long 1 # Small
    .long 2 # Big
    .long 2 # Fire
    .long 0 # Mini
    .long 3 # Propeller
    .long 2 # Penguin
    .long 2 # Ice
    .long 2 # Acorn
    .long 2 # PAcorn
    # Begin custom data
    .long 2

#? BlahTable from NSMBW
# TODO: What does this do? It's HitboxCollider related [distToCenter]
#* Index corresponds to ARRAY_1016d7cc entries
ARRAY_101e6d1c:
    .long 0x1016D694
    .long 0x1016D6A4
    .long 0x1016D6B4
    .long 0x1016D6C4
    .long 0x1016D6D4
    .long 0x1016D6E4
    .long 0x1016D6F4
    .long 0x1016D624
    .long 0x1016D634
    .long 0x1016D644
    .long 0x1016D654
    .long 0x1016D664
    .long 0x1016D674
    .long 0x1016D684
    # Begin custom data

#? SomePowerupRelatedTable / SomeTable from NSMBW
# TODO: What does this do? It's HitboxCollider related [distToEdge]
#* Index corresponds to ARRAY_1016d7cc entries
ARRAY_101e6d54:
    .long 0x1016D704
    .long 0x1016D714
    .long 0x1016D724
    .long 0x1016D734
    .long 0x1016D744
    .long 0x1016D754
    .long 0x1016D764
    .long 0x1016D624
    .long 0x1016D634
    .long 0x1016D644
    .long 0x1016D654
    .long 0x1016D664
    .long 0x1016D674
    .long 0x1016D684
    # Begin custom data
    .long 0x1016D684
    .long 0x1016D684
    .long 0x1016D684
    .long 0x1016D684
    .long 0x1016D684
    .long 0x1016D684

#? WeirdScaleTable from NSMBW
# TODO: What does the index correspond to?
PowerupCenterOffsetTable:
    .float 16.0
    .float 16.0
    .float 31.0
    .float 31.0
    .float 6.0
    .float 31.0
    .float 31.0
    .float 31.0
    .float 31.0
    .float 31.0
    # Begin custom data
    .float 31.0
    .float 31.0
    .float 31.0
    .float 31.0
    .float 31.0
    .float 31.0

# Index corresponds to PowerupState
ARRAY_1016cd68:
    .float 0.0  # Small
    .float -4.0 # Big
    .float -4.0 # Fire
    .float 4.0  # Mini
    .float -5.0 # Propeller
    .float -2.0 # Penguin
    .float -4.0 # Ice
    .float -4.0 # Acorn
    .float -4.0 # PAcorn
    # Begin custom data
    .float -4.0

# Index corresponds to PowerupState
ARRAY_1016ce20:
    .float -10.0 # Small
    .float 9.0   # Big
    .float 0.0   # Fire
    .float -7.0  # Mini
    .float 6.0   # Propeller
    .float 15.9  # Penguin
    .float 4.0   # Ice
    .float 12.0  # Acorn
    .float 15.9  # PAcorn
    # Begin custom data
    .float 9.0

# Index corresponds to PowerupState
ARRAY_1016ce44:
    .float -5.0 # Small
    .float 4.0  # Big
    .float 4.0  # Fire
    .float -2.0 # Mini
    .float 1.0  # Propeller
    .float 27.0 # Penguin
    .float 8.0  # Ice
    .float 23.0 # Acorn
    .float 7.9  # PAcorn
    # Begin custom data
    .float 4.0

# Index corresponds to PowerupState
ARRAY_1016d7f8:
    .float 0.6 # Small
    .float 1.0 # Big
    .float 1.0 # Fire
    .float 0.1 # Mini
    .float 0.6 # Propeller
    .float 0.6 # Penguin
    .float 0.1 # Ice
    .float 0.6 # Acorn
    .float 0.6 # PAcorn
    # Begin custom data
    .float 0.6

.text

.global AnotherProjectilePowerupCheck
AnotherProjectilePowerupCheck:
    cmpwi r8, 2
    beqlr

    # Extra types here

    cmpwi r8, 9
    blr

.global AllowThrowingProjectile
AllowThrowingProjectile:
    # If comparison is true we will continue to throw

    # Ice flower
    cmpwi r0, 6
    beqlr

    # Extra types here

    # Kamek Hat
    cmpwi r0, 9
    blr

.global ProjectileExtraTypes
ProjectileExtraTypes:
    # If comparison is true we will throw a fireball (or the hijacked equivalent)

    # Fire Flower
    cmpwi r0, 2
    beqlr

    # Extra types here

    # Kamek Hat
    cmpwi r0, 9
    blr

.global ShouldThrowProjectile
ShouldThrowProjectile: # Custom version of Player::ShouldThrowProjectile
    lis       r11, DAT_101c30d0@ha
    lwz       r0, 0x500(r3)

    cmpwi     r0, 2
    beq       ShouldThrowProjectileIsFire

    # Extra types here

    cmpwi     r0, 9
    bne       ShouldThrowProjectileIsNotFire

.global ShouldThrowProjectile_2
ShouldThrowProjectile_2:
    lis       r12, DAT_101c30d0@ha
    lwz       r0, 0x500(r3)


    cmpwi     r0, 2
    beq       ShouldThrowProjectile_2IsFire

    # Extra types here

    cmpwi     r0, 9
    bne       ShouldThrowProjectile_2NotFire

ShouldThrowProjectileIsFire:
    cmpwi     r4, 0
    bne       ShouldThrowProjectileReturn1
    lbz       r10, 0x54(r3)
    lwz       r12, DAT_101c30d0@l(r11)
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
    lwz       r12, DAT_101c30d0@l(r11)
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
    lwz       r12, DAT_101c30d0@l(r12)
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
    lwz       r12, DAT_101c30d0@l(r12)
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
    # Load powerup state
    lwz r3, 0x500(r30)

    # Kamek hat
    cmpwi r3, 9
    li r3, 387 # Projectile profile ID
    beq SpawnProjectile

    # Extra types here

    # Otherwise fire
    li r3, 0x1DC
SpawnProjectile:
    b get__7ProfileSFUi

.global UseCustomTallTypeTable
UseCustomTallTypeTable:
    lis   r0, PowerupTallTypeTable@h
    slwi  r12, r4, 2
    ori   r0, r0, PowerupTallTypeTable@l
    lwzx  r3, r12, r0
    blr

.global UseCustomSensorSizeTable
UseCustomSensorSizeTable: # r12 is array index
    # Custom address
    lis  r0, PowerupSensorSizeTable@h
    ori  r0, r0, PowerupSensorSizeTable@l

    # Load from it
    lfsx f1, r12, r0

    blr

.global UseCustomPowerupCenterOffsetTable
UseCustomPowerupCenterOffsetTable:
    lis r11, PowerupCenterOffsetTable@ha
    addi r11, r11, PowerupCenterOffsetTable@l
    blr

.global UseCustomPowerupCenterOffsetTable_2
UseCustomPowerupCenterOffsetTable_2:
    lis r10, PowerupCenterOffsetTable@ha
    blr

.global UseCustomPowerupCenterOffsetTable_3
UseCustomPowerupCenterOffsetTable_3:
    lfs f1, PowerupCenterOffsetTable@l(r10)

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

.global UseCustomArray_1016d7cc
UseCustomArray_1016d7cc: # Custom version of Player::vfA5C
    lwz       r7, 0x2750(r3)
    lwz       r12, 0x500(r3)
    lis       r0, ARRAY_1016d7cc@h
    lwz       r10, 0xC4(r7)
    slwi      r11, r12, 2
    ori       r0, r0, ARRAY_1016d7cc@l
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


