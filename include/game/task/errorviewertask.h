#pragma once

#include <sead/task.h>

class ErrorViewerTask : public sead::CalculateTask {
public:
    static ErrorViewerTask* instance() { return sInstance; }

protected:
    static ErrorViewerTask* sInstance;
};
