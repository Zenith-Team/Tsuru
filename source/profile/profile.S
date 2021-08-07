.include "registers.S"

.text

.global SpriteToProfileList_r3
SpriteToProfileList_r3:
    addis     r7, r12, spriteToProfileList__7Profile@ha
    lwz       r3, spriteToProfileList__7Profile@l(r7)
    blr

.global SpriteToProfileList_r3_2
SpriteToProfileList_r3_2:
    addis     r8, r10, spriteToProfileList__7Profile@ha
    addi      r3, r8, spriteToProfileList__7Profile@l
    blr

.global SpriteToProfileList_r19
SpriteToProfileList_r19:
    lis       r19, spriteToProfileList__7Profile@ha
    addi      r19, r19, spriteToProfileList__7Profile@l
    blr

.global SpriteToProfileList_r22
SpriteToProfileList_r22:
    lis       r22, spriteToProfileList__7Profile@ha
    addi      r22, r22, spriteToProfileList__7Profile@l
    blr

.global SpriteToProfileList_r24
SpriteToProfileList_r24:
    lis       r24, spriteToProfileList__7Profile@ha
    addi      r24, r24, spriteToProfileList__7Profile@l
    blr

.global SpriteToProfileList_r26
SpriteToProfileList_r26:
    lis       r26, spriteToProfileList__7Profile@ha
    addi      r26, r26, spriteToProfileList__7Profile@l
    blr

.global SpriteToProfileList_r30
SpriteToProfileList_r30:
    lis       r30, spriteToProfileList__7Profile@ha
    addi      r30, r30, spriteToProfileList__7Profile@l
    blr

.global SpriteToProfileList_r31
SpriteToProfileList_r31:
    lis       r31, spriteToProfileList__7Profile@ha
    addi      r31, r31, spriteToProfileList__7Profile@l
    blr

.global loadNumProfiles_r29
loadNumProfiles_r29:
    mflr      r0
    addi      r1, r1, -0x20
    stw       r0, 0x24(r1)

    mr        r30, r3
    bl        getNumProfiles__7ProfileSFv
    mr        r29, r3
    mr        r3, r30

    lwz       r0, 0x24(r1)
    addi      r1, r1, 0x20
    mtlr      r0
    blr

.global loadNumProfiles_r30
loadNumProfiles_r30:
    mflr      r0
    addi      r1, r1, -0x20
    stw       r0, 0x24(r1)

    mr        r29, r3
    bl        getNumProfiles__7ProfileSFv
    mr        r30, r3
    mr        r3, r29

    lwz       r0, 0x24(r1)
    addi      r1, r1, 0x20
    mtlr      r0
    blr
