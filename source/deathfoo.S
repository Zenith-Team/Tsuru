.rodata
DarkColor:     .byte    5, 0, 0, 255
LightColor:    .byte    145, 0, 55, 255
CloudDistance: .float   20.0
DeathFooRes:   .string "huhd"

.text

# Enum for foo cloud types (nybble 11)
.set CloudTypeCustom, 0xB
.set CloudTypeFoo,    0x1
.set CloudTypeDeath,  0x5

# Foo actor patches

.global SetSpawnedCloudType
SetSpawnedCloudType:
    li r29, 0x10 # Foo cloud type
    cmpwi r0, 0x2 # NoCloud is set to 2
    bnelr
    li r29, 0xB0 # Custom cloud type
    blr

.global SetDeathFooTexture
SetDeathFooTexture:
    lwz   r0, 0x18C0(r28) # Load this->noCloud
    cmpwi r0, 0x0
    lis   r0, 0x1009
    subic r0, r0, 0x5984
    beqlr
    lis   r0, DeathFooRes@h
    ori   r0, r0, DeathFooRes@l
    blr

# Cloud actor patches

.global RedirectCloudType
RedirectCloudType:
    # Compare against custom and foo cloud types and return the comparison result
    # If either are true, it will call the SpawnedByFoo onExecute branch

    cmpwi r0, CloudTypeCustom
    beqlr

    cmpwi r0, CloudTypeFoo
    blr

.global SetCloudTexture
SetCloudTexture:
    # Compare against custom and death cloud types and return the comparison result
    # If either are true, it will set the cloud tex anim frame to the death cloud one

    cmpwi r7, CloudTypeCustom
    beqlr

    cmpwi r7, CloudTypeDeath
    blr

.global SetCloudDarkColor
SetCloudDarkColor:
    # Replaced instruction
    mr     r15, r28

    # Return if not custom type
    lwz    r9, 0x10(r31) # Load this->settings1
    extrwi r9, r9, 4, 24 # r9 = r9 >> 4 & 0xF
    cmpwi  r9, CloudTypeCustom
    bnelr

    # Set the dark color
    lis    r9, DarkColor@ha
    addi   r9, r9, DarkColor@l
    stw    r9, 0x10(r1)

    blr

.global SetCloudLightColor
SetCloudLightColor:
    # Skip loading custom color if not custom type
    lwz    r10, 0x10(r31) # Load this->settings1
    extrwi r10, r10, 4, 24 # r9 = r9 >> 4 & 0xF
    cmpwi  r10, CloudTypeCustom
    bne    StoreLightColor

    # Color.. stuff
    lis r10, LightColor@ha
    lbzu r9, LightColor@l(r10)
    insrwi r26, r9, 8, 0
    lbz r9, 1(r10)
    insrwi r26, r9, 8, 8
    lbz r9, 2(r10)
    insrwi r26, r9, 8, 16
StoreLightColor:
    stw    r26, 0x0(r7)
    blr

.global CloudCollision
CloudCollision:
    # Get the distance to player
    mflr r23
    bl ASM_VECDistance

    # Check cloud type
    lwz r12, 0x10(r31) # Load this->settings1
    extrwi r12, r12, 4, 24 # r12 = r12 >> 4 & 0xF
    cmpwi r12, CloudTypeCustom

    # Restore context
    mtlr r23
    li r23, 10

    # Return if not custom type
    bnelr

    # Return if cloud is too far
    lis r12, CloudDistance@ha
    lfs f6, CloudDistance@l(r12)
    fcmpu cr0, f1, f6
    bgelr

    # Return if cloud is too transparent (inactive)
    clrlwi. r12, r26, 24
    cmpwi r12, 0xE0
    blelr

    mflr r23
    fmr f16, f1

    # Load address to player damage function
    lwz r12, 0x4C(r11)
    lwz r12, 0x8E4(r12)
    mtctr r12

    # Call player damage function
    mr r3, r11 # param 1: this
    li r4, 0   # param 2: idk
    li r5, 0xF # param 3: damageType: InstaKill_2
    bctrl

    # Restore context and return
    fmr f1, f16
    mtlr r23
    li r23, 10
    blr
