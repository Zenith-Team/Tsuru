#pragma once

#include "sead/task.h"

class DRCModeTask : public sead::CalculateTask {
public:
    static DRCModeTask* sInstance;
};
