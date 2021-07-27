#pragma once

#include "sead/task.h"

class ErrorViewerTask : public sead::CalculateTask {
public:
    static ErrorViewerTask* sInstance;
};
