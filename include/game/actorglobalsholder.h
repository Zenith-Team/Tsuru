#pragma once

#include "sead/idisposer.h"

class BossController;

class ActorGlobalsHolder { // Size: 0x9F4
    SEAD_SINGLETON_DISPOSER(ActorGlobalsHolder);

public:
    u8 _10[0x18 - 0x10];
    BossController* activeBossController;
    u8 _1C[2520];
};
