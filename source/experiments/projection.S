.include "macros.S"

.text

.global MakePerspectiveLevel
MakePerspectiveLevel:
    # Safely branch to the C++ function
    SafeBranch makePerspectiveLevel__Fv

    # Restore replaced instruction and return
    li r5, 0x0
    blr
