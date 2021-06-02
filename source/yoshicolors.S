.rodata
YoshiTexPink:       .string "Yoshi_TexPink"
YoshiTexLightBlue:  .string "Yoshi_TexLightBlue"
YoshiTexYellow:     .string "Yoshi_TexYellow"

.text
.include "registers.S"

.global PatchYoshiColors
PatchYoshiColors:
    # Patch Pink Yoshi
    lis      r0, YoshiTexPink@h
    ori      r0, r0, YoshiTexPink@l
    stw      r0, 0x8(r12)

    # Patch Light Blue Yoshi
    lis      r0, YoshiTexLightBlue@h
    ori      r0, r0, YoshiTexLightBlue@l
    stw      r0, 0x10(r12)

    # Patch Yellow Yoshi
    lis      r0, YoshiTexYellow@h
    ori      r0, r0, YoshiTexYellow@l
    stw      r0, 0x18(r12)

    blr

.global RandomYoshiColors
RandomYoshiColors:
    stwu     sp, -0x4(sp)
    mflr     r0
    stw      r0, 0x8(sp)

    lis      r3, instance__Q2_4sead12GlobalRandom@ha
    lwz      r3, instance__Q2_4sead12GlobalRandom@l(r3)
    bl       getU32__Q2_4sead6RandomFv
    li       r4, 0x4
    mulhwu   r4, r3, r4
    mr       r3, r29

    lwz      r0, 0x8(sp)
    mtlr     r0
    addi     sp, sp, 0x4
    blr
