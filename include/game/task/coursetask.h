#pragma once

#include <sead/task.h>

class CourseTask : public sead::CalculateTask { // Size: 0x5A8 (custom) 0x5A4 (original)
    SEAD_SINGLETON_TASK(CourseTask)

public:
    u8 _4[0x5A4 - 0x4];
    bool sizeModifierEnabled;   // Custom member
};

