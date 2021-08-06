.include "registers.S"
.include "macros.S"

.rodata
//TestString: .string "ErrorWindow_BtnIC_OK_00"
PatchString: .short 0x0077, 0x006F, 0x006D, 0x0061, 0x006E, 0x0020, 0x0063, 0x0075, 0x006D, 0x0000 # Woman Cum
VersionStringMsbtID: .string "Title_Ver_00" 

.data
isVersionString: .word 0 # bool

.text

.global PatchStringSize
PatchStringSize:
    lis r31, isVersionString@h
    ori r31, r31, isVersionString@l
    lwz r31, 0x0(r31)
    cmpwi r31, 0x0
    mr r31, r3
    beqlr
    lis r31, PatchString@h
    ori r31, r31, PatchString@l
    stw r31, 0x30(sp)
    lis r31, isVersionString@h
    ori r31, r31, isVersionString@l
    li r3, 0x0
    stw r3, 0x0(r31)
    li r31, 9
    blr

.global CheckIfShouldPatchString
CheckIfShouldPatchString:
    lwz r4, 0x0(r29)
    lis r3, VersionStringMsbtID@h
    ori r3, r3, VersionStringMsbtID@l
    SafeBranch strcmp
    cmpwi r3, 0x0
    bne CheckIfShouldPatchStringReturn
    lis r3, isVersionString@h
    ori r3, r3, isVersionString@l
    li r4, 0x1
    stw r4, 0x0(r3)
CheckIfShouldPatchStringReturn:
    lwz r4, 0x0(r29)
    blr
