#pragma once

#include "framework/seadTaskMgr.h"
#include "framework/seadCalculateTask.h"

class CourseTask : public sead::CalculateTask {
    SEAD_TASK_SINGLETON_DISPOSER(CourseTask);

public:
    static sead::TaskBase* construct(const sead::TaskConstructArg& arg);
};
