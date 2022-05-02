.include "macros.S"

.global LevelResPreloaderCaller
LevelResPreloaderCaller:
    SafeBranch levelResPreloader__Fv
    lwz r5, 0xC(r24)
    blr
