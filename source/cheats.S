.include "macros.S"

.global InfiniteLives
InfiniteLives:
    SaveVolatileRegisters

    # Load SHSaveMgr::sSaveData.infiniteLivesEnabled
    lis     r3, sSaveData__12TsuruSaveMgr@ha
    addi    r3, r3, sSaveData__12TsuruSaveMgr@l
    lbz     r4, 0x4(r3)

    # If it's on then restore registers and return false
    cmpwi   r4, 1
    beq     SafeReturn

    # Otherwise restore replaced instruction and continue the function
    RestoreVolatileRegisters
    mflr    r0
    stwu    sp, -0x4(sp)
    stw     r3, 0x8(sp)
    lis     r3, 0x024c
    addi    r3, r3, 0x005c
    mtctr   r3
    lwz     r3, 0x8(sp)
    addi    sp, sp, 0x4
    bctr    # 0x24c005c

.global InfiniteTime
InfiniteTime:
    SaveVolatileRegisters

    # Load SHSaveMgr::sSaveData.infiniteTimeEnabled
    lis     r3, sSaveData__12TsuruSaveMgr@ha
    addi    r3, r3, sSaveData__12TsuruSaveMgr@l
    lbz     r4, 0x5(r3)

    # If it's on then restore registers and return false
    cmpwi   r4, 1
    beq     SafeReturn

    # Otherwise restore replaced instruction and continue the function
    RestoreVolatileRegisters
    mflr    r0
    stwu    sp, -0x4(sp)
    stw     r3, 0x8(sp)
    lis     r3, 0x024c
    addi    r3, r3, 0x1388
    mtctr   r3
    lwz     r3, 0x8(sp)
    addi    sp, sp, 0x4
    bctr    # 0x24c1388

.global NoClip
NoClip:
    SaveVolatileRegisters

    # Load SHSaveMgr::sSaveData.noClipEnabled
    lis     r3, sSaveData__12TsuruSaveMgr@ha
    addi    r3, r3, sSaveData__12TsuruSaveMgr@l
    lbz     r4, 0x6(r3)

    # If it's on then skip setting the sensor
    cmpwi   r4, 1
    beq     SafeReturn

    # Otherwise continue to set the sensor
    RestoreVolatileRegisters
    stwu    sp, -0x4(sp)
    mflr    r0
    stw     r0, 0x8(sp)
    bl      setSensor__10PhysicsMgrFPCQ2_10PhysicsMgr6SensorUi
    lwz     r0, 0x8(sp)
    mtlr    r0
    addi    sp, sp, 0x4
    blr

.global Invincibility
Invincibility:
    SaveVolatileRegisters

    # Load SHSaveMgr::sSaveData.invincibilityEnabled
    lis     r3, sSaveData__12TsuruSaveMgr@ha
    addi    r3, r3, sSaveData__12TsuruSaveMgr@l
    lbz     r4, 0x7(r3)

    # If it's on then restore registers and return false
    cmpwi   r4, 1
    beq     SafeReturn

    # Otherwise restore replaced instruction and continue the function
    RestoreVolatileRegisters
    mflr    r0
    stwu    sp, -0x4(sp)
    stw     r3, 0x8(sp)
    lis     r3, 0x0293
    addi    r3, r3, 0x1180
    mtctr   r3
    lwz     r3, 0x8(sp)
    addi    sp, sp, 0x4
    bctr    # 0x2931180
