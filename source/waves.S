.include "macros.S"

.text

.global SetWaterWaveValues
SetWaterWaveValues:
    SaveVolatileRegisters

    mr r3, r30
    bl setWaterWaveValues__FP10EnvTerrain

    RestoreVolatileRegisters

    cmpwi r0, 0
    blr

.global WaveCollision_r4
WaveCollision_r4:
    # Check for lava waves
    li    r3, 4 # Return value
    cmpwi r4, 1 # Lava wave
    beqlr

    # Check for water waves
    li    r3, 1 # Return value
    cmpwi r4, 2 # Water wave
    beqlr

    # Must be poison waves
    li    r3, 5 # Return value
    blr

.global WaveCollision_r12
WaveCollision_r12:
    # Check for lava waves
    li    r3,  4 # Return value
    cmpwi r12, 1 # Lava wave
    beqlr

    # Check for water waves
    li    r3,  1 # Return value
    cmpwi r12, 2 # Water wave
    beqlr

    # Check for poison waves
    li    r3,  5 # Return value
    blr
