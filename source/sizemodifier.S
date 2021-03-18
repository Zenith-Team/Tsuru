.rodata
ActorScales: .float 1.0, 0.25, 0.5, 0.75, 1.25, 1.5, 1.75, 2.0, 2.5, 3.0, 4.0, 5.0, 6.0, 7.0, 7.5, 10.0

.text
.include "asmsetup.S"

.global ScaleModel
ScaleModel:
    lbz r0, 0x19(r3)
    cmpwi r0, 0xF
    bgtlr
    rlwinm r0, r0, 0x2, 0x0, 0x1D
    lis r12, ActorScales@ha
    addi r12, r12, ActorScales@l
    lfsx f0, r12, r0
    lfs f11, 0x90(r3)
    fmuls f11, f11, f0
    stfs f11, 0x90(r3)
    lfs f11, 0x94(r3)
    fmuls f11, f11, f0
    stfs f11, 0x94(r3)
    lfs f11, 0x98(r3)
    fmuls f11, f11, f0
    stfs f11, 0x98(r3)

    blr

.global ScaleCollision
ScaleCollision:
    li r8, 0x0

    lbz r0, 0x19(r4)
    cmpwi r0, 0xF
    bgtlr
    rlwinm r0, r0, 0x2, 0x0, 0x1D
    lis r12, ActorScales@ha
    addi r12, r12, ActorScales@l
    lfsx f0, r12, r0
    lfs f11, 0x74(r30)
    fmuls f11, f11, f0
    stfs f11, 0x74(r30)
    lfs f11, 0x78(r30)
    fmuls f11, f11, f0
    stfs f11, 0x78(r30)
    lfs f11, 0x7C(r30)
    fmuls f11, f11, f0
    stfs f11, 0x7C(r30)
    lfs f11, 0x80(r30)
    fmuls f11, f11, f0
    stfs f11, 0x80(r30)

    blr
