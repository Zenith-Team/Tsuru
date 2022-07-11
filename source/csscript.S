.text

.global UseCustomCSScripts1
UseCustomCSScripts1:
    lis r9, CSScriptsTable@h
    ori r9, r9, CSScriptsTable@l
    add r9, r9, r11
    lwz r9, 0x4(r9)
    blr

.global UseCustomCSScripts2
UseCustomCSScripts2:
    lis r0, CSScriptsTable@h
    ori r0, r0, CSScriptsTable@l
    slwi r12, r12, 0x3
    lwzx r3, r12, r0
    blr
