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
#ifdef __DEBUG # Only log the name if debug is enabled
    # Allocate 0x38 bytes from stack
    stwu sp,  -0x38(sp)

    # Save registers to stack
    stw  r0,  0x08(sp)
    stw  r3,  0x0C(sp)
    stw  r4,  0x10(sp)
    stw  r5,  0x14(sp)
    stw  r6,  0x18(sp)
    stw  r7,  0x1C(sp)
    stw  r8,  0x20(sp)
    stw  r9,  0x24(sp)
    stw  r10, 0x28(sp)
    stw  r11, 0x2C(sp)
    stw  r12, 0x30(sp)
    mfcr r0
    stw  r0,  0x34(sp)
    mflr r0
    stw  r0,  0x3C(sp)

    # Call the C++ function
    bl LogWorldMapScript

    # Restore registers from stack
    lwz  r0,  0x34(sp)
    mtcr r0
    lwz  r0,  0x3C(sp)
    mtlr r0
    lwz  r0,  0x08(sp)
    lwz  r3,  0x0C(sp)
    lwz  r4,  0x10(sp)
    lwz  r5,  0x14(sp)
    lwz  r6,  0x18(sp)
    lwz  r7,  0x1C(sp)
    lwz  r8,  0x20(sp)
    lwz  r9,  0x24(sp)
    lwz  r10, 0x28(sp)
    lwz  r11, 0x2C(sp)
    lwz  r12, 0x30(sp)

    # Restore stack pointer
    addi sp,  sp, 0x38

#endif # ifdef __DEBUG

    # Restore replaced instruction and return
    cmpwi r0, 0xFF
    blr
