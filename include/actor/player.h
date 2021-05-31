#pragma once

#include "actor/playerbase.h"

// TODO: methods, members, verify

class Player : public PlayerBase {
public:
    bool vf8CC(StageActor*, u32);
    bool setDamageState(StageActor*, u32); // 8D4
};
