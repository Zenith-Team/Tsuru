.text
.include "macros.S"
.include "registers.S"

.global Waves_onCreate
Waves_onCreate:
    SafeBranch Waves_onCreate__FP10EnvTerrain

    # Restore replaced instruction and return
    cmpwi r0, 0x0
    blr

.global Waves_onExecute
Waves_onExecute:
    SaveVolatileRegisters

    # Set r3 to be TerrainEffects*
    addi r3, r30, 0x1AE4

    # Branch to C++ function
    bl Waves_onExecute__FP14TerrainEffects

    RestoreVolatileRegisters

    # Restore replaced instruction and return
    cmpwi r0, 0x0
    blr
