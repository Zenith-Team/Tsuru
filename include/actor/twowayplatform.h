#pragma once

#include "actor.h"

class ColliderBase;
class Vec2;

class TwoWayPlatform : public Actor
{
 public:
    static bool cbCallback4(Actor*);
    static bool cbCallback5(Actor*);
    static bool cbCallback6(Actor*, u32, u32);

    bool twoWayPlatformCbCallback2(ColliderBase*, Vec2*);
};
