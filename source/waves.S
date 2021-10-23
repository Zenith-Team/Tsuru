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
WaveCollision_r4: # r4 is TileMgr::instance()->waveType
    # Check for lava waves
    li    r3, 4 # Return value
    cmpwi r4, 1 # Lava wave
    beqlr

    # Check for water waves
    li    r3, 1 # Return value
    cmpwi r4, 2 # Water wave
    beqlr

    # Check for poison waves
    li    r3, 5 # Return value
    cmpwi r4, 3
    beqlr

    # Must be quicksand waves
    li    r3, 2
    blr

.global WaveCollision_r12
WaveCollision_r12: # r12 is TileMgr::instance()->waveType
    # Check for lava waves
    li    r3,  4 # Return value
    cmpwi r12, 1 # Lava wave
    beqlr

    # Check for water waves
    li    r3,  1 # Return value
    cmpwi r12, 2 # Water wave
    beqlr

    # Check for poison waves
    li    r3, 5 # Return value
    cmpwi r12, 3
    beqlr

    # Must be quicksand waves
    li    r3, 2
    blr
