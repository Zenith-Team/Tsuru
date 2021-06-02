.include "registers.S"

.global custom_world_map_scripts_table

.global WorldMapScriptsHook1
WorldMapScriptsHook1:
    lis     r9,     custom_world_map_scripts_table@h
    ori     r9, r9, custom_world_map_scripts_table@l
    blr

.global WorldMapScriptsHook2
WorldMapScriptsHook2:
    lis     r0,     custom_world_map_scripts_table@h
    ori     r0, r0, custom_world_map_scripts_table@l
    slwi    r12, r12, 3
    lwzx    r3, r12, r0
    blr
