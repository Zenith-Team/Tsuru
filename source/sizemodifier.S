.include "macros.S"

.rodata
ActorScales: .float 1.0, 0.25, 0.5, 0.75, 1.25, 1.5, 1.75, 2.0, 2.5, 3.0, 4.0, 5.0, 6.0, 7.0, 7.5, 10.0

.text

.global CourseTaskCtorExtension
CourseTaskCtorExtension:
    SaveVolatileRegisters

    li      r4, 0x0
    lis     r3, sInstance__10CourseTask@ha
    addi    r3, r3, sInstance__10CourseTask@l
    stw     r4, 0x5A4(r3) # CourseTask::sizeModifierEnabled

    RestoreVolatileRegisters
    blr

.global ScaleActor
ScaleActor:
    # Check if should scale actor
    lis     r12, sInstance__10CourseTask@ha
    addi    r12, r12, sInstance__10CourseTask@l
    lbz     r12, 0x5A4(r12)
    cmpwi   r12, 1
    bnelr

    # All clear

    lbz     r0, 0x19(r3)             # r3 is the actor pointer (Actor*) so we load linkID into r0
    cmpwi   r0, 0xF
    bgtlr                            # return if linkID > 0xF

    rlwinm  r0, r0, 0x2, 0x0, 0x1D   # r0 = r0 << 0x2

    lis     r12, ActorScales@ha
    addi    r12, r12, ActorScales@l

    lfsx    f0, r12, r0              # f0 = r12[r0]

    # Multiply scale.x
    lfs     f11, 0x90(r3)
    fmuls   f11, f11, f0
    stfs    f11, 0x90(r3)

    # Multiply scale.y
    lfs     f11, 0x94(r3)
    fmuls   f11, f11, f0
    stfs    f11, 0x94(r3)

    # Multiply scale.z
    lfs     f11, 0x98(r3)
    fmuls   f11, f11, f0
    stfs    f11, 0x98(r3)

    # Multiply visibleAreaOffset.x
    lfs     f11, 0x1E4(r3)
    fmuls   f11, f11, f0
    stfs    f11, 0x1E4(r3)

    # Multiply visibleAreaOffset.y
    lfs     f11, 0x1E8(r3)
    fmuls   f11, f11, f0
    stfs    f11, 0x1E8(r3)

    # Multiply visibleAreaSize.x
    lfs     f11, 0x1EC(r3)
    fmuls   f11, f11, f0
    stfs    f11, 0x1EC(r3)

    # Multiply visibleAreaSize.y
    lfs     f11, 0x1F0(r3)
    fmuls   f11, f11, f0
    stfs    f11, 0x1F0(r3)

    blr

.global ScaleHitboxCollider
ScaleHitboxCollider:
    li      r8, 0x0                     # Replaced instruction

    # Check if should scale actor
    lis     r12, sInstance__10CourseTask@ha
    addi    r12, r12, sInstance__10CourseTask@l
    lbz     r12, 0x5A4(r12)
    cmpwi   r12, 1
    bnelr

    # All clear

    lbz     r0, 0x19(r4)                # r4 is the actor pointer (Actor*) so we load linkId into r0
    cmpwi   r0, 0xF
    bgtlr                               # return if linkId > 0xF

    rlwinm  r0, r0, 0x2, 0x0, 0x1D      # r0 = r0 << 0x2

    lis     r12, ActorScales@ha
    addi    r12, r12, ActorScales@l

    lfsx     f0, r12, r0                # f0 = r12[r0]

    # Multiply distToCenter.x
    lfs     f11, 0x74(r30)
    fmuls   f11, f11, f0
    stfs    f11, 0x74(r30)

    # Multiply distToCenter.y
    lfs     f11, 0x78(r30)
    fmuls   f11, f11, f0
    stfs    f11, 0x78(r30)

    # Multiply distToEdge.x
    lfs     f11, 0x7C(r30)
    fmuls   f11, f11, f0
    stfs    f11, 0x7C(r30)

    # Multiply distToEdge.y
    lfs     f11, 0x80(r30)
    fmuls   f11, f11, f0
    stfs    f11, 0x80(r30)

    blr

.global ScalePhysicsMgr
ScalePhysicsMgr:
    # Check if should scale actor
    lis     r6, sInstance__10CourseTask@ha
    addi    r6, r6, sInstance__10CourseTask@l
    lbz     r6, 0x5A4(r6)
    cmpwi   r6, 1
    bnelr

    # All clear

    # Load this->owner->linkID << 0x2
    lwz     r6, 0x890(r3)
    lbz     r6, 0x19(r6)

    # Return if linkID > 0xF
    cmpwi   r6, 0xF
    bgtlr

    # r6 = r6 << 0x2
    rlwinm  r6, r6, 0x2, 0x0, 0x1D

    lis     r7, ActorScales@ha
    addi    r7, r7, ActorScales@l

    lfsx    f0, r7, r6              # f0 = r7[r0]

    # Multiply sensor->point1
    lfs     f11, 0x0(r4)
    fmuls   f11, f11, f0
    stfs    f11, 0x928(r12)

    # Multiply sensor->point2
    lfs     f11, 0x4(r4)
    fmuls   f11, f11, f0
    stfs    f11, 0x92C(r12)

    # Multiply sensor->distanceFromCenter
    lfs     f11, 0x8(r4)
    fmuls   f11, f11, f0
    stfs    f11, 0x930(r12)

    blr
