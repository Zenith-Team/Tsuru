.text
.include "macros.S"
.include "globals.S"
.include "registers.S"

.global custom_world_map_scripts_table

.global WorldMapScriptsHook1
WorldMapScriptsHook1:
    lis     r9,     custom_world_map_scripts_table@h
    ori     r9, r9, custom_world_map_scripts_table@l
    add     r9, r9, r11
    lwz     r9, 4(r9)
    blr

.global WorldMapScriptsHook2
WorldMapScriptsHook2:
    lis     r0,     custom_world_map_scripts_table@h
    ori     r0, r0, custom_world_map_scripts_table@l
    slwi    r12, r12, 3
    lwzx    r3, r12, r0
    blr

.global PrintMapScriptName
PrintMapScriptName:
.if DEBUG
    SafeBranch LogWorldMapScript
.endif

    # Restore replaced instruction and return
    cmpwi r0, 0xFF
    blr
