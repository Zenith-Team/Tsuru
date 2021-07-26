.text
.include "registers.S"

.global Return
Return:
    blr

.global ReturnFalse
ReturnFalse:
    li r3, 0x0
    blr

.global ReturnTrue
ReturnTrue:
    li r3, 0x1
    blr
