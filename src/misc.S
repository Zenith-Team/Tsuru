.include "macros.S"

.rodata

.global sInstance__14GameSetupScene
sInstance__14GameSetupScene: .long 0

.text

.global CastleSwingUpdateModel
CastleSwingUpdateModel:
    SaveVolatileRegisters
    lwz r12, 0x4C(r31) # vtable
    lwz r0, 0x44(r12)
    mtctr r0
    mr r3, r31
    bctrl
    RestoreVolatileRegisters
    lwz r0, 0x14(r1) # Replaced instruction
    lwz r31, 0xC(r1)
    mtlr r0
    addi r1, r1, 0x10
    li r3, 1
    blr

.global GameSetupScene_SetInstance
GameSetupScene_SetInstance:
    lis r3, sInstance__14GameSetupScene@ha
    addi r3, r3, sInstance__14GameSetupScene@l
    stw r30, 0x0(r3)
    mr r3, r31
    blr

.global GameSetupScene_ClearInstance
GameSetupScene_ClearInstance:
    lis r3, sInstance__14GameSetupScene@ha
    addi r3, r3, sInstance__14GameSetupScene@l
    li r31, 0
    stw r31, 0x0(r3)
    blr

.global SetCurrentGraphicsContext
SetCurrentGraphicsContext:
    mr r31, r3
    SaveVolatileRegisters

    lis r3, CurrentGraphicsContext@ha
    addi r3, r3, CurrentGraphicsContext@l

    # First part
    lbz r4, 0x0(r31)
    stb r4, 0x0(r3)
    lbz r4, 0x1(r31)
    stb r4, 0x1(r3)
    lwz r4, 0x4(r31)
    stw r4, 0x4(r3)
    lwz r4, 0x8(r31)
    stw r4, 0x8(r3)
    lbz r4, 0xC(r31)
    stb r4, 0xC(r3)
    lwz r4, 0x10(r31)
    stw r4, 0x10(r3)
    lwz r4, 0x14(r31)
    stw r4, 0x14(r3)
    lwz r4, 0x18(r31)
    stw r4, 0x18(r3)
    lwz r4, 0x1C(r31)
    stw r4, 0x1C(r3)
    lwz r4, 0x20(r31)
    stw r4, 0x20(r3)
    lwz r4, 0x24(r31)
    stw r4, 0x24(r3)

    # Color4f
    addi r5, r31, 0x28
    lfs f0, 0x0(r5)
    stfs f0, 0x0(r3)
    lfs f0, 0x4(r5)
    stfs f0, 0x4(r3)
    lfs f0, 0x8(r5)
    stfs f0, 0x8(r3)
    lfs f0, 0xC(r5)

    # Second part
    stfs f0, 0xC(r3)
    lbz r4, 0x38(r31)
    stb r4, 0x38(r3)
    lwz r4, 0x3C(r31)
    stw r4, 0x3C(r3)
    lfs f0, 0x40(r31)
    stfs f0, 0x40(r3)
    lbz r4, 0x44(r31)
    stb r4, 0x44(r3)
    lbz r4, 0x45(r31)
    stb r4, 0x45(r3)
    lbz r4, 0x46(r31)
    stb r4, 0x46(r3)
    lbz r4, 0x47(r31)
    stb r4, 0x47(r3)
    lbz r4, 0x48(r31)
    stb r4, 0x48(r3)
    lwz r4, 0x4C(r31)
    stw r4, 0x4C(r3)
    lwz r4, 0x50(r31)
    stw r4, 0x50(r3)
    lwz r4, 0x54(r31)
    stw r4, 0x54(r3)
    lwz r4, 0x58(r31)
    stw r4, 0x58(r3)
    lwz r4, 0x5C(r31)
    stw r4, 0x5C(r3)
    lwz r4, 0x60(r31)
    stw r4, 0x60(r3)

    # RenderState
    addi r5, r31, 0x64
    lwz r4, 0x0(r5)
    stw r4, 0x0(r3)
    lwz r4, 0x4(r5)
    stw r4, 0x4(r3)
    lbz r4, 0x8(r5)
    stb r4, 0x8(r3)
    lbz r4, 0x9(r5)
    stb r4, 0x9(r3)
    lbz r4, 0xA(r5)
    stb r4, 0xA(r3)

    RestoreVolatileRegisters
    blr

.global SetBossActorType
SetBossActorType:
    li r0, 5
    stb r0, 0x20D(r31)

    lwz r0, 0x14(r1)
    lwz r31, 0xC(r1)
    mtlr r0
    addi r1, r1, 0x10
    li r3, 1
    blr

.global IsPlayerUp
IsPlayerUp:
    # Check if player is holding up and set projectile buildInfo->settings2 to 1 is so
    lwz r3, 0x2B0(r30)
    rlwinm r3, r3, 0x1C, 0x1F, 0x1F
    cmpi r3, 0
    beq IsPlayerUp_exit
    stw r3, 0x40(sp)

IsPlayerUp_exit:
    lwz r9, 0x280(r30)
    blr

.global PlayerProjectileSpeed
PlayerProjectileSpeed:
    # Set projectile speed if settings2 != 0
    mr r3, r30
    SafeBranch setProjectileSpeed__FP10StageActor
    lwz r0, 0x14(r1)
    blr
