.text
.include "macros.S"
.include "registers.S"

.global ReportPowerup
ReportPowerup:
    SaveVolatileRegisters
    bl LogPowerup__FP10PlayerBase
    RestoreVolatileRegisters

    stw r0, 0x14(r1)
    blr
