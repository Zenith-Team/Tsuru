#pragma once

#include <sead.h>

class TaskMgr {
    SEAD_SINGLETON_DISPOSER(TaskMgr)

public:
    bool startLevel(sead::TaskBase* currentTask, u8 world, u8 level);
    bool changeTask(sead::TaskBase* currentTask, sead::TaskClassID& taskClassID, u32 unk1, u32 unk2);
};
