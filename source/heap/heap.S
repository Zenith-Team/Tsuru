.include "macros.S"

.text

.global CreateTsuruHeap
CreateTsuruHeap:
    SafeBranch createTsuruHeap__Fv
    blr
