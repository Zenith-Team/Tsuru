.text
.include "globals.S"
.include "registers.S"

.global CollisionDebugDraw
CollisionDebugDraw:
.if DEBUG
    lis  r9, debugDraw__8AreaTaskFRCQ3_3agl3lyr10RenderInfo@ha
    addi r9, r9, debugDraw__8AreaTaskFRCQ3_3agl3lyr10RenderInfo@l
.endif
    blr
