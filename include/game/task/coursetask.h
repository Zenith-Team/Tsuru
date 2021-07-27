#pragma once

#include "sead/task.h"

class CourseTask : public sead::CalculateTask {
public:
    static CourseTask* sInstance;
};
