#pragma once

#include <sead/idisposer.h>

class PlayerDemoMgr
{
    SEAD_SINGLETON_DISPOSER(PlayerDemoMgr);

public:

    void startControlDemoAll_1();
    void endControlDemoAll();
};
