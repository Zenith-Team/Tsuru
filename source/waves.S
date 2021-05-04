.text
.include "registers.S"

.global AllocEventWaves
AllocEventWaves:
    addi  r3, r3, 0x10
    b     __nw__FUi

.global InitWaterWaves
InitWaterWaves:
    mr    r3, r31
    b     initWaterWaves__FP10EnvTerrainP4Vec3fbT4Q2_14TerrainEffects11TerrainTypePQ2_4sead4Heap # I hope this is right

.global UpdateWaterWaves
UpdateWaterWaves:
    mr    r3, r31
    mflr  r31
    bl    updateWaterWaves__FP14TerrainEffects
    mtlr  r31
    lwz   r0, 0x1C(r1)

    blr

.global WaterWaveCollision
WaterWaveCollision:
    # Lava waves
    li    r3,  0x4
    cmpwi r4,  0x1
    beqlr

    # Water waves
    li    r3,  0x1
    cmpwi r4,  0x2
    beqlr

    # Poison waves
    li    r3,  0x5
    blr

.global WaterWaveCollision2
WaterWaveCollision2:
    # Lava waves
    li    r3,  0x4
    cmpwi r12, 0x1
    beqlr

    # Water waves
    li    r3,  0x1
    cmpwi r12, 0x2
    beqlr

    # Poison waves 
    li    r3,  0x5
    blr
