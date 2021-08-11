.text

.global AreaTaskDebugDraw
AreaTaskDebugDraw:
    lis     r9, drawLayerDebug__8AreaTaskFRCQ3_3agl3lyr10RenderInfo@ha
    addi    r9, r9, drawLayerDebug__8AreaTaskFRCQ3_3agl3lyr10RenderInfo@l
    blr

.global CourseSelectTaskDebugDraw
CourseSelectTaskDebugDraw:
    lis     r0, drawLayerDebug__16CourseSelectTaskFRCQ3_3agl3lyr10RenderInfo@h
    ori     r0, r0, drawLayerDebug__16CourseSelectTaskFRCQ3_3agl3lyr10RenderInfo@l
    stw     r0, 0xC(r5)
    blr
