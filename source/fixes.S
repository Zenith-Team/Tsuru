.rodata
cast_double: .quad 0x4330000080000000

.text
.include "registers.S"

.global DistantViewMgr_AddBGOffset
DistantViewMgr_AddBGOffset:
    # Allocate 0x18 bytes from stack
    stwu  r1, -0x18(r1)

    # Stuff needed for casting integral type to floating-point type
    lis   r9, cast_double@ha
    lfd   f0, cast_double@l(r9)
    lis   r0, 0x4330
    stw   r0, 0x8(r1)

    # Load s16 from r24+0x2 (xOffs) into r9 and cast it to f32 into f8
    lha   r9, 0x2(r24)
    xoris r9, r9, 0x8000
    stw   r9, 0xC(r1)
    lfd   f8, 0x8(r1)
    fsub  f8, f8, f0
    frsp  f8, f8

    # Increment f32 at r29+0x234 (xPos, loaded into f9) by f8 (xOffs)
    lfs   f9, 0x234(r29)
    fadds f9, f9, f8
    stfs  f9, 0x234(r29)

    # Load s16 from r24+0x4 (yOffs) into r9 and cast it to f32 into f8
    lha   r9, 0x4(r24)
    xoris r9, r9, 0x8000
    stw   r9, 0xC(r1)
    lfd   f8, 0x8(r1)
    fsub  f8, f8, f0
    frsp  f8, f8

    # Decrement f32 at r29+0x238 (yPos, loaded into f9) by f8 (yOffs)
    lfs   f9, 0x238(r29)
    fsubs f9, f9, f8
    stfs  f9, 0x238(r29)

    # Load s16 from r24+0x6 (zOffs) into r9 and cast it to f32 into f8
    lha   r9, 0x6(r24)
    xoris r9, r9, 0x8000
    stw   r9, 0xC(r1)
    lfd   f8, 0x8(r1)
    fsub  f8, f8, f0
    frsp  f8, f8

    # Increment f32 at r29+0x23C (zPos, loaded into f9) by f8 (zOffs)
    lfs   f9, 0x23C(r29)
    fadds f9, f9, f8
    stfs  f9, 0x23C(r29)

    # Restore stack pointer
    addi  r1, r1, 0x18

    # Restore replaced instruction and return
    addi  r9, r24, 0x8
    blr
