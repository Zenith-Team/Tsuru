.include "macros.S"

.macro CheckSaveMember offset
    # Load SHSaveMgr::sSaveData.offset
    lis   r3, sSaveData__12TsuruSaveMgr@ha
    addi  r3, r3, sSaveData__12TsuruSaveMgr@l
    lbz   r4, offset(r3)

    # If it's on then restore registers and return false
    cmpwi r4, 1
    beq   SafeReturn
.endm

# Enum of the save data members
.set infiniteLivesEnabled, 0x4
.set infiniteTimeEnabled,  0x5
.set noClipEnabled,        0x6
.set invincibilityEnabled, 0x7

.global InfiniteLives
InfiniteLives:
    SaveVolatileRegisters

    CheckSaveMember infiniteLivesEnabled

    # Otherwise restore replaced instruction and continue the function
    RestoreVolatileRegisters
    mflr    r0
    stwu    sp, -0x4(sp)
    stw     r3, 0x8(sp)
    lis     r3, InfiniteLivesContinue@ha
    addi    r3, r3, InfiniteLivesContinue@l
    mtctr   r3
    lwz     r3, 0x8(sp)
    addi    sp, sp, 0x4
    bctr    # 0x24c005c

.global InfiniteTime
InfiniteTime:
    SaveVolatileRegisters

    CheckSaveMember infiniteTimeEnabled

    # Otherwise restore replaced instruction and continue the function
    RestoreVolatileRegisters
    mflr    r0
    stwu    sp, -0x4(sp)
    stw     r3, 0x8(sp)
    lis     r3, InfiniteTimeContinue@ha
    addi    r3, r3, InfiniteTimeContinue@l
    mtctr   r3
    lwz     r3, 0x8(sp)
    addi    sp, sp, 0x4
    bctr    # 0x24c1388

.global NoClip
NoClip:
    SaveVolatileRegisters

    CheckSaveMember noClipEnabled

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

    CheckSaveMember invincibilityEnabled

    # Otherwise restore replaced instruction and continue the function
    RestoreVolatileRegisters
    mflr    r0
    stwu    sp, -0x4(sp)
    stw     r3, 0x8(sp)
    lis     r3, InvincibilityContinue@ha
    addi    r3, r3, InvincibilityContinue@l
    mtctr   r3
    lwz     r3, 0x8(sp)
    addi    sp, sp, 0x4
    bctr    # 0x2931180

SafeReturn:
    RestoreVolatileRegisters
    blr
