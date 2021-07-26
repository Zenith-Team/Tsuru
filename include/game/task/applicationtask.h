#pragma once

#include "sead/task.h"

class ApplicationTask : public sead::CalculateTask {
public:
    static ApplicationTask* sInstance;
};
