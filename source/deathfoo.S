.rodata
DeathCloudColorDark:    .byte 5, 0, 0, 255
DeathCloudColorLight:   .byte 145, 0, 55, 255
DeathCloudSize:         .float 1.0

.text
.include "asmsetup.S"

.global FooCloudType_onCreate
FooCloudType_onCreate:
    # Nybble 12 is checked
	bnelr
	lwz     r29, 0x10(r30)
	b       FooCloudType

.global FooCloudType_breathIn
FooCloudType_breathIn:
	# Nybble 12 is checked
    bnelr
	lwz     r29, 0x10(r31)

.global FooCloudType
FooCloudType:
	srwi.   r29, r29, 28
	beqlr
	li      r29, 0xB0

	blr

.global FooCloudUpdate
FooCloudUpdate:
	cmpwi   r0, 0xB
	beqlr
	cmpwi   r0, 1

	blr

.global FooCloudTexture
FooCloudTexture:
	cmpwi   r7, 0xB
	beqlr
	cmpwi   r7, 5

	blr

.global FooCloudColorDark
FooCloudColorDark:
	mr      r15, r28
	lwz     r9, 0x10(r31)
	extrwi  r9, r9, 4, 24
	cmpwi   r9, 0xB
	bnelr
	
	lis     r9,     DeathCloudColorDark@h
	ori     r9, r9, DeathCloudColorDark@l
	stw     r9, 0x10(r1)

	blr

.global FooCloudColorLight
FooCloudColorLight:
	lwz     r10, 0x10(r31)
	extrwi  r10, r10, 4, 24
	cmpwi   r10, 0xB
	bne     StoreLightCloudColor
	
	lis     r10, DeathCloudColorLight@ha
	lbzu    r9,  DeathCloudColorLight@l(r10)
	insrwi  r26, r9, 8, 0

	lbz     r9,  1(r10)
	insrwi  r26, r9, 8, 8

	lbz     r9,  2(r10)
	insrwi  r26, r9, 8, 16

.global StoreLightCloudColor
StoreLightCloudColor:
	stw     r26, 0(r7)

	blr

.global DeathFooCollision
DeathFooCollision:
	mflr    r23
	bl      ASM_VECDistance
	lwz     r12, 0x10(r31)
	extrwi  r12, r12, 4, 24
	cmpwi   r12, 0xB
	mtlr    r23
	li      r23, 10
	bnelr
	
	lis     r12, DeathCloudSize@ha
	lfs     f6,  DeathCloudSize@l(r12)
	fcmpu   cr0, f1, f6
	bgelr
	
	# Check the transparency
	clrlwi. r12, r26, 24
	cmpwi   r12, 0xE0
	blelr
	
	mflr    r23
	fmr     f16, f1
	lwz     r12, 0x4C(r11)
	lwz     r12, 0x8D4(r12)

	mtctr   r12
	mr      r3,  r11
	li      r4,  0
	li      r5,  0x10
	bctrl
	fmr     f1,  f16
	mtlr    r23
	li      r23, 10

	blr
