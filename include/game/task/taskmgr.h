#pragma once

#include "math/seadVector.h"
#include "heap/seadDisposer.h"
#include "framework/seadTaskMgr.h"

class TaskMgr {
    SEAD_SINGLETON_DISPOSER(TaskMgr);

public:
    // Switches to CourseTask and starts a level
    // @param currentTask A pointer to the instance of the currently running task
    // @param world Target world ID
    // @param level Target level ID
    bool startLevel(sead::TaskBase* currentTask, u8 world, u8 level);

    // Changes the current game task to a new target one
    // @param currentTask A pointer to the instance of the currently running task
    // @param taskClassID A reference to a taskClassID structure representing the new task
    bool changeTask(sead::TaskBase* currentTask, sead::TaskClassID& taskClassID, u32 = 0, u32 = 0);

    u8 _10[0x74 - 0x10]; // TODO
    sead::Vector3f faderPos;
    u8 _80[0x84 - 0x80]; // TODO
};
