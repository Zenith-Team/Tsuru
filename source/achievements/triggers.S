.include "macros.S"

.global Collect3UpMoon
Collect3UpMoon:
    SafeBranch achieveGet3Up__18AchievementManagerSFv
    cmpwi r3, 0x0
    blr
