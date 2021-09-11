.include "macros.S"

.data
BeepBlockStateTimer: .word 0

.text

.global UpdateBeepBlockStates
UpdateBeepBlockStates:
    SaveVolatileRegisters

    # Load pointer to timer variable
    lis     r3, BeepBlockStateTimer@ha
    addi    r3, r3, BeepBlockStateTimer@l
    lwz     r4, 0x0(r3)

    # If it's 240 (4 seconds) then toggle the state
    cmpwi   r4, 240
    beq     ToggleBeepBlockState

    # Otherwise increment the timer and return
    addi    r4, r4, 1
    stw     r4, 0x0(r3)

    b       SafeReturn

ToggleBeepBlockState:
    # Reset the timer
    li      r4, 0
    stw     r4, 0x0(r3)

    # Load beep block state
    lis     r3, CurrentBeepBlockState__9BeepBlock@ha
    addi    r3, r3, CurrentBeepBlockState__9BeepBlock@l
    lwz     r4, 0x0(r3)

    # If it's red then change it to blue
    cmpwi   r4, 0
    beq     ChangeBeepBlockStateToBlue

    # Otherwise make it red
    li      r4, 0
    stw     r4, 0x0(r3)

    b SafeReturn

ChangeBeepBlockStateToBlue:
    li      r4, 1
    stw     r4, 0x0(r3)

    b SafeReturn
