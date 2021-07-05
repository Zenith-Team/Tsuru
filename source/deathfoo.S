.rodata
CloudSize: .float 1.0

.text
.include "macros.S"
.include "registers.S"

# This function is currently unused as right now it just uses NoCloud=1 as the death foo enable nybble
.global CheckDeathFooNybble
CheckDeathFooNybble:
	cmpwi r0, 0x0
	beqlr
	li 	  r29, 0xB0
	blr

.global RedirectCustomCloudTypeOnExecute
RedirectCustomCloudTypeOnExecute:
	# Check if cloud type is 0xB
	cmplwi r0, 0xB

	# Load the address of the CloudTypeIs1 label
	SaveVolatileRegisters
	lis    r3, 	   onExecute__5CloudFv__CloudTypeIs1@ha
	ori    r3, r3, onExecute__5CloudFv__CloudTypeIs1@l
	mtctr  r3
	RestoreVolatileRegisters

	# Branch to it if cloud type is 0xB
	beqctr

	# Otherwise restore replaced instruction and return
	cmplwi r0, 0x5
	blr

.global CustomCloudColorBase
CustomCloudColorBase:
	# Load the CloudType nybble
	lwz     r9, 0x10(r31)
	extrwi  r9, r9, 4, 24

	# Return if type is not 0xB
	cmpwi   r9, 0xB
	bnelr

	# Load the custom base color and store it
	# Hex color code: #050000
	lis     r9, 0x0500
	stw     r9, 0x10(r1)

	# Restore replaced instruction and return
	mr      r15, r28
	blr

.global CustomCloudColorHighlight
CustomCloudColorHighlight:
	# Check if cloud type is 0xB
	lwz     r10, 0x10(r31)
	extrwi  r10, r10, 4, 24
	cmpwi   r10, 0xB

	# If so store the default color
	bne     StoreFooCloudColorHighlight

	# Otherwise let's load the custom highlight color
	# Hex color code: #910037
	lis     r26, 	  0x9100
	ori		r26, r26, 0x3700

	# And store it
	b 		StoreFooCloudColorHighlight

StoreFooCloudColorHighlight:
	# Restore replaced instruction and return
	stw     r26, 0x0(r7) # r7: 421605ec
	blr

.global CustomCloudTexture
CustomCloudTexture:
	# wtf how does this even do anything??

	cmpwi   r7, 0xB
	beqlr
	cmpwi   r7, 5

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

	lis     r12, CloudSize@ha
	lfs     f6,  CloudSize@l(r12)
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
