.text
.include "asmsetup.S"

.global FakeStarCoin
FakeStarCoin:
    stw r0, 0x3C(r1)
    lwz r4, 0x14(r3)
    extrwi. r4, r4, 1, 7 # Checkbox at nybble 14
    beqlr

    bl 
