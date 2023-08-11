#pragma once

#include "sead/runtimetypeinfo.h"

namespace sead {

class TaskParameter {
public:
    SEAD_RTTI_BASE(TaskParameter);
};

static_assert(sizeof(TaskParameter) == 0x4, "sead::TaskParameter size mismatch");

}
