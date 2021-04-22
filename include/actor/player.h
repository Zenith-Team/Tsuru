#pragma once

#include "playerbase.h"

// TODO: methods, members, verify

class Player : public PlayerBase {
public:
    bool vf8CC(Actor*, u32);
    bool setDamageState(Actor*, u32); // 8D4
};
