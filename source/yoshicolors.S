.rodata
YoshiTexPink: .string "Yoshi_TexPink"
YoshiTexLightBlue: .string "Yoshi_TexLightBlue"
YoshiTexYellow: .string "Yoshi_TexYellow"

.text
.include "asmsetup.S"

.global PatchYoshiColors
PatchYoshiColors:
    # Patch Pink Yoshi
    lis r0, YoshiTexPink@h
    ori r0, r0, YoshiTexPink@l
    stw r0, 0x8(r12)

    # Patch Light Blue Yoshi
    lis r0, YoshiTexLightBlue@h
    ori r0, r0, YoshiTexLightBlue@l
    stw r0, 0x10(r12)

    # Patch Yellow Yoshi
    lis r0, YoshiTexYellow@h
    ori r0, r0, YoshiTexYellow@l
    stw r0, 0x18(r12)

    blr
