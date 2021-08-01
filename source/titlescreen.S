.include "registers.S"

//.rodata
//VersionString: .string ":("

.text

.global PatchVersionString
PatchVersionString:
    li r5, 0x3 // Number of args to format version string
    li r6, 0x9 // Arg 1
    li r7, 0x9 // Arg 2
    li r8, 0x9 // Arg 3
    //lis r9, VersionString@h
    //ori r9, r9, VersionString@l
    //stw r9, 0x1f00(r30)
    //stw r9, 0x1f0c(r30)
    blr
