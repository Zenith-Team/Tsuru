.include "macros.S"

.text

.global SetPhysicsMgrOwner
SetPhysicsMgrOwner:
    stw r31, 0x890(r3)  # this->owner = owner
    SafeBranch setSensor__10PhysicsMgrFPCQ2_10PhysicsMgr6SensorUi
    blr

.global SetCurrentGraphicsContext
SetCurrentGraphicsContext:
    mr r31, r3
    SaveVolatileRegisters

    lis r3, CurrentGraphicsContext@ha
    addi r3, r3, CurrentGraphicsContext@l

    lbz r4, 0x0(r31)
    stb r4, 0x0(r3)
    lbz r4, 0x1(r31)
    stb r4, 0x1(r3)
    lwz r4, 0x4(r31)
    stw r4, 0x4(r3)
    lwz r4, 0x8(r31)
    stw r4, 0x8(r3)
    lbz r4, 0xc(r31)
    stb r4, 0xc(r3)
    lwz r4, 0x10(r31)
    stw r4, 0x10(r3)
    lwz r4, 0x14(r31)
    stw r4, 0x14(r3)
    lwz r4, 0x18(r31)
    stw r4, 0x18(r3)
    lwz r4, 0x1c(r31)
    stw r4, 0x1c(r3)
    lwz r4, 0x20(r31)
    stw r4, 0x20(r3)
    lwz r4, 0x24(r31)
    stw r4, 0x24(r3)

    addi r5, r31, 0x28
    lfs f0, 0x0(r5)
    stfs f0, 0x0(r3)
    lfs f0, 0x4(r5)
    stfs f0, 0x4(r3)
    lfs f0, 0x8(r5)
    stfs f0, 0x8(r3)
    lfs f0, 0xc(r5)

    stfs f0, 0xc(r3)
    lbz r4, 0x38(r31)
    stb r4, 0x38(r3)
    lwz r4, 0x3c(r31)
    stw r4, 0x3c(r3)
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
    lwz r4, 0x4c(r31)
    stw r4, 0x4c(r3)
    lwz r4, 0x50(r31)
    stw r4, 0x50(r3)
    lwz r4, 0x54(r31)
    stw r4, 0x54(r3)
    lwz r4, 0x58(r31)
    stw r4, 0x58(r3)
    lwz r4, 0x5c(r31)
    stw r4, 0x5c(r3)
    lwz r4, 0x60(r31)
    stw r4, 0x60(r3)

    addi r5, r31, 0x64
    lwz r4, 0x0(r5)
    stw r4, 0x0(r3)
    lwz r4, 0x4(r5)
    stw r4, 0x4(r3)
    lbz r4, 0x8(r5)
    stb r4, 0x8(r3)
    lbz r4, 0x9(r5)
    stb r4, 0x9(r3)
    lbz r4, 0xa(r5)
    stb r4, 0xa(r3)

    RestoreVolatileRegisters
    blr
