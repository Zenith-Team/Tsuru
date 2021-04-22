.text
.include "asmsetup.S"

.global LoadCustomSpriteList_02004578
LoadCustomSpriteList_02004578:
    lis     r22, spriteToProfileList__7Profile@ha       # Load our custom spriteToProfileList in r22
    addi    r22, r22, spriteToProfileList__7Profile@l   # ^
    cmplwi  r9, 0x9999                                  # Remove the sprite count check
    blr                                                 # Return

.global LoadCustomSpriteList_02004DA8
LoadCustomSpriteList_02004DA8:
    lis     r7, spriteToProfileList__7Profile@ha        # Load our custom spriteToProfileList in r7
    addi    r7, r7, spriteToProfileList__7Profile@l     # ^
    add     r7, r7, r12                                 # r7 = r7 + r12
    lwz     r3, 0x0(r7)                                 # r3 = *r7
    blr                                                 # Return

.global LoadCustomSpriteList_02005018
LoadCustomSpriteList_02005018:
    lis     r19, spriteToProfileList__7Profile@ha       # Load our custom spriteToProfileList in r19
    addi    r19, r19, spriteToProfileList__7Profile@l   # ^
    cmplwi  r6, 0x9999                                  # Remove the sprite count check
    blr                                                 # Return

.global LoadCustomSpriteList_02007C60_0200806C_02008260
LoadCustomSpriteList_02007C60_0200806C_02008260:
    lis     r24, spriteToProfileList__7Profile@ha       # Load our custom spriteToProfileList in r24
    addi    r24, r24, spriteToProfileList__7Profile@l   # ^
    cmplwi  r0, 0x9999                                  # Remove the sprite count check
    blr                                                 # Return

.global LoadCustomSpriteList_0200844C
LoadCustomSpriteList_0200844C:
    lis     r26, spriteToProfileList__7Profile@ha       # Load our custom spriteToProfileList in r26
    addi    r26, r26, spriteToProfileList__7Profile@l   # ^
    cmplwi  r0, 0x9999                                  # Remove the sprite count check
    blr                                                 # Return

.global LoadCustomSpriteList_020086A0
LoadCustomSpriteList_020086A0:
    lis     r31, spriteToProfileList__7Profile@ha       # Load our custom spriteToProfileList in r31
    addi    r31, r31, spriteToProfileList__7Profile@l   # ^
    lwzx    r9, r11, r31                                # r9 = r31[r11]
    blr                                                 # Return

.global LoadCustomSpriteList_0200A830
LoadCustomSpriteList_0200A830:
    lis     r30, spriteToProfileList__7Profile@ha       # Load our custom spriteToProfileList in r30
    addi    r30, r30, spriteToProfileList__7Profile@l   # ^
    lwzx    r29, r11, r30                               # r29 = r30[r11]
    blr                                                 # Return
