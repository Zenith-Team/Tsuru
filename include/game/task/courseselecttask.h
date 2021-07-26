#pragma once

#include "sead/task.h"

class CourseSelectTask : public sead::CalculateTask {
public:
    static CourseSelectTask* sInstance;
};
