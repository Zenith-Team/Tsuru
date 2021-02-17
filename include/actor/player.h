#pragma once

#include "actor.h"

class PlayerBase : public Actor { };
class Player : public PlayerBase
{
public:
    bool vf8CC(Actor*, u32);
    bool setDamageState(Actor*, u32); // 8D4
};
