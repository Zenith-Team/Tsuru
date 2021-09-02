.include "macros.S"

.text

.global SetPhysicsMgrOwner
SetPhysicsMgrOwner:
    stw r31, 0x890(r3)  # this->owner = owner
    SafeBranch setSensor__10PhysicsMgrFPCQ2_10PhysicsMgr6SensorUi
    blr
