#pragma once

#include "actor/stageactor.h"

class TwoWayPlatform : public StageActor {
public:
    static bool cbCallback4(StageActor*);
    static bool cbCallback5(StageActor*);
    static bool cbCallback6(StageActor*, u32, u32);

    bool twoWayPlatformCbCallback2(ColliderBase*, Vec2*);
};
