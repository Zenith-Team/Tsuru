.include "macros.S"

.text

# Enum
.set WaveType_Lava, 1
.set WaveType_Water, 2
.set WaveType_Poison, 3
.set WaveType_Quicksand, 4

# Enum
.set WaveCollision_Lava, 4
.set WaveCollision_Water, 1
.set WaveCollision_Poison, 5
.set WaveCollision_Quicksand, 2

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
    li    r3, WaveCollision_Lava # Return value
    cmpwi r4, WaveType_Lava
    beqlr

    # Check for water waves
    li    r3, WaveCollision_Water # Return value
    cmpwi r4, WaveType_Water
    beqlr

    # Check for poison waves
    li    r3, WaveCollision_Poison # Return value
    cmpwi r4, WaveType_Poison
    beqlr

    # Must be quicksand waves
    li    r3, WaveCollision_Quicksand
    blr

.global WaveCollision_r12
WaveCollision_r12: # r12 is TileMgr::instance()->waveType
    # Check for lava waves
    li    r3,  WaveCollision_Lava # Return value
    cmpwi r12, WaveType_Lava
    beqlr

    # Check for water waves
    li    r3,  WaveCollision_Water # Return value
    cmpwi r12, WaveType_Water
    beqlr

    # Check for poison waves
    li    r3, WaveCollision_Poison # Return value
    cmpwi r12, WaveType_Poison
    beqlr

    # Must be quicksand waves
    li    r3, WaveCollision_Quicksand
    blr
