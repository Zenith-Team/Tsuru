.include "macros.S"

.extern sInstance__8CheatMgr

.global Invincibility
Invincibility:
    SaveVolatileRegisters

    # Load CheatMgr::sInstance.mInvincibilityEnabled
    lis     r3, sInstance__8CheatMgr@ha
    addi    r3, r3, sInstance__8CheatMgr@l
    lbz     r4, 0x3(r3)

    # If it's on restore registers and return false
    cmpwi   r4, 1
    beq     InvincibilityEnabled

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
    bctr
InvincibilityEnabled:
    RestoreVolatileRegisters
    b       ReturnFalse
