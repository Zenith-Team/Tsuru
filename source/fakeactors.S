.text
.include "asmsetup.S"

.global FakeStarCoin
FakeStarCoin:
    stw r0, 0x3C(r1)
    lwz r4, 0x14(r3)
    extrwi. r4, r4, 1, 7 # Checkbox at nybble 14
    beqlr

    bl fakeStarCoin__FP5Actor

    lwz r28, 0x28(r1)
	lwz r29, 0x2C(r1)
	lwz r0, 0x3C(r1)
	lwz r30, 0x30(r1)
	mtlr r0
	lwz r31, 0x34(r1)
	addi r1, r1, 0x38

	blr
