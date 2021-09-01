#pragma once

#include <sead/task.h>

class RootTask : public sead::CalculateTask {
    SEAD_SINGLETON_TASK(RootTask)

public:
    RootTask(const sead::TaskConstructArg& arg);

    static sead::TaskBase* construct(const sead::TaskConstructArg& arg);
    
};
