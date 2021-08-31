#pragma once

#include <sead/task.h>

class CourseTask : public sead::CalculateTask {
public:
    static CourseTask* instance() { return sInstance; }

protected:
    static CourseTask* sInstance;
};
