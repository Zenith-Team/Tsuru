.include "macros.S"

.text

.global MakePerspectiveLevel
MakePerspectiveLevel:
    # Safely branch to the C++ function
    SafeBranch makePerspectiveLevel__Fv

    # Restore replaced instruction and return
    li r5, 0x0
    blr

.global RedirectToFrustumCtor
RedirectToFrustumCtor:
    b __ct__Q2_4sead17FrustumProjectionFfN51

.global RedirectToFrustumDtor
RedirectToFrustumDtor:
    b __dt__Q2_4sead17FrustumProjectionFv
