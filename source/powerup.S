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
    .long 0x1016d694
    .long 0x1016d6a4
    .long 0x1016d6b4
    .long 0x1016d6c4
    .long 0x1016d6d4
    .long 0x1016d6e4
    .long 0x1016d6f4
    .long 0x1016d624
    .long 0x1016d634
    .long 0x1016d644
    .long 0x1016d654
    .long 0x1016d664
    .long 0x1016d674
    .long 0x1016d684
    # Begin custom data

#? SomePowerupRelatedTable / SomeTable from NSMBW
# TODO: What does this do? It's HitboxCollider related [distToEdge]
#* Index corresponds to ARRAY_1016d7cc entries
ARRAY_101e6d54:
    .long 0x1016d704
    .long 0x1016d714
    .long 0x1016d724
    .long 0x1016d734
    .long 0x1016d744
    .long 0x1016d754
    .long 0x1016d764
    .long 0x1016d624
    .long 0x1016d634
    .long 0x1016d644
    .long 0x1016d654
    .long 0x1016d664
    .long 0x1016d674
    .long 0x1016d684
    # Begin custom data
    .long 0x1016d684
    .long 0x1016d684
    .long 0x1016d684
    .long 0x1016d684
    .long 0x1016d684
    .long 0x1016d684

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

.global ShouldThrowProjectile_2
ShouldThrowProjectile_2:
    lis       r12, DAT_101c30d0@ha
    lwz       r0, 0x500(r3)


    cmpwi     r0, 2
    beq       ShouldThrowProjectile_2IsFire

    # Extra types here

    cmpwi     r0, 9
    bne       ShouldThrowProjectile_2NotFire

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
    blt       ShouldThrowProjectile_2Return1
ShouldThrowProjectile_2Return0:
    li        r3, 0
    blr
ShouldThrowProjectile_2NotFire:
    cmpwi     r0, 5
    beq       ShouldThrowProjectile_2NotIce
    cmpwi     r0, 6
    bne       ShouldThrowProjectile_2Return0
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
    bge       ShouldThrowProjectile_2Return0
ShouldThrowProjectile_2Return1:
    li        r3, 1
    blr

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
