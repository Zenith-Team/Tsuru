.text

.global RedirectToCustomYoshiTexArray
RedirectToCustomYoshiTexArray:
    # r4 = &YoshiTexArray + (r30 * 8)
    lis      r4, YoshiTexArray@ha
    addi     r4, r4, YoshiTexArray@l
    mr       r3, r30
    mulli    r3, r3, 8
    add      r4, r4, r3
    mr       r3, r31
    blr

.global RandomYoshiColors
RandomYoshiColors:
    # Save LR
    stwu     sp, -0x4(sp)
    mflr     r0
    stw      r0, 0x8(sp)

    # sead::Random::getU32(sead::GlobalRandom::sInstance)
    lis      r3, sInstance__Q2_4sead12GlobalRandom@ha
    lwz      r3, sInstance__Q2_4sead12GlobalRandom@l(r3)
    bl       getU32__Q2_4sead6RandomFv

    lis      r4, YoshiTexNum@ha
    lwz      r4, YoshiTexNum@l(r4)
    mulhwu   r4, r3, r4
    mr       r3, r29

    # Restore LR
    lwz      r0, 0x8(sp)
    mtlr     r0
    addi     sp, sp, 0x4
    blr
