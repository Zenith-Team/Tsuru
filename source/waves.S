.include "macros.S"

.text

# Enum
.set wave_lava,      1
.set wave_water,     2
.set wave_poison,    3
.set wave_quicksand, 4

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
    cmpwi r4, wave_lava
    beqlr

    # Check for water waves
    li    r3, 1 # Return value
    cmpwi r4, wave_water
    beqlr

    # Check for poison waves
    li    r3, 5 # Return value
    cmpwi r4, wave_poison
    beqlr

    # Must be quicksand waves
    li    r3, 2
    blr

.global WaveCollision_r12
WaveCollision_r12: # r12 is TileMgr::instance()->waveType
    # Check for lava waves
    li    r3,  4 # Return value
    cmpwi r12, wave_lava
    beqlr

    # Check for water waves
    li    r3,  1 # Return value
    cmpwi r12, wave_water
    beqlr

    # Check for poison waves
    li    r3, 5 # Return value
    cmpwi r12, wave_poison
    beqlr

    # Must be quicksand waves
    li    r3, 2
    blr
