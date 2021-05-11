.text
.include "registers.S"

.global CollisionDebugDraw
CollisionDebugDraw:
    lis     r9, debugDraw__8AreaTaskFRCQ3_3agl3lyr10RenderInfo@ha
    addi    r9, r9, debugDraw__8AreaTaskFRCQ3_3agl3lyr10RenderInfo@l
    blr
