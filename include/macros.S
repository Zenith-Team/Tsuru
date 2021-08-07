.macro SaveVolatileRegisters
    stwu sp,  -0x38(sp)
    stw  r0,  0x08(sp)
    stw  r3,  0x0C(sp)
    stw  r4,  0x10(sp)
    stw  r5,  0x14(sp)
    stw  r6,  0x18(sp)
    stw  r7,  0x1C(sp)
    stw  r8,  0x20(sp)
    stw  r9,  0x24(sp)
    stw  r10, 0x28(sp)
    stw  r11, 0x2C(sp)
    stw  r12, 0x30(sp)
    mfcr r0
    stw  r0,  0x34(sp)
    mflr r0
    stw  r0,  0x3C(sp)
.endm

.macro RestoreVolatileRegisters
    lwz  r0,  0x34(sp)
    mtcr r0
    lwz  r0,  0x3C(sp)
    mtlr r0
    lwz  r0,  0x08(sp)
    lwz  r3,  0x0C(sp)
    lwz  r4,  0x10(sp)
    lwz  r5,  0x14(sp)
    lwz  r6,  0x18(sp)
    lwz  r7,  0x1C(sp)
    lwz  r8,  0x20(sp)
    lwz  r9,  0x24(sp)
    lwz  r10, 0x28(sp)
    lwz  r11, 0x2C(sp)
    lwz  r12, 0x30(sp)
    addi sp,  sp, 0x38
.endm

.macro SafeBranch Function
    SaveVolatileRegisters
    bl Function
    RestoreVolatileRegisters
.endm
