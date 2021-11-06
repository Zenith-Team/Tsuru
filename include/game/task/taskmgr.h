#pragma once

#include <sead.h>

class TaskMgr {
    SEAD_SINGLETON_DISPOSER(TaskMgr)

public:
    // Switches to CourseTask and starts a level
    // @param currentTask A pointer to the instance of the currently running task
    // @param world Target world ID
    // @param level Target level ID
    bool startLevel(sead::TaskBase* currentTask, u8 world, u8 level);

    // Changes the current game task to a new target one
    // @param currentTask A pointer to the instance of the currently running task
    // @param taskClassID A reference to a taskClassID structure representing the new task
    // @param u32 Unknown. Set to 0 if unsure
    // @param u32 Unknown. Set to 0 if unsure
    bool changeTask(sead::TaskBase* currentTask, sead::TaskClassID& taskClassID, u32, u32);
};
