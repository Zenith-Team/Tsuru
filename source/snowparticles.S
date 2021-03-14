.text
.include "asmsetup.S"

.global SnowSave
SnowSave:
    lwz r30, 0x10(r31)
    stw r30, 0x1934(r31)
    lwz r30, 0x14(r31)
    stw r30, 0x1938(r31)

    blr

.global Snow1RaA
Snow1RaA:
    lbz r4, 0xb0(r28)
    lbz r0, 0xb3(r28)

    blr

.global Snow1B
Snow1B:
    lbz r10, 0xb2(r28)

    blr

.global Snow1G
Snow1G:
    lbz r5, 0xb1(r28)

    blr

.global Snow2R
Snow2R:
    lbz r4, 0xb4(r28)

    blr

.global Snow2GaB
Snow2GaB:
    lbz r5, 0xb5(r28)
    lbz r6, 0xb6(r28)

    blr

.global Snow2A
Snow2A:
    lbz r0, 0xb7(r28)

    blr
