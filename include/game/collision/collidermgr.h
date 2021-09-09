#pragma once

#include <game/collision/solid/colliderbase.h>

class ColliderMgr {
    SEAD_SINGLETON_DISPOSER(ColliderMgr)

public:
    void add(ColliderBase* collider);
    void remove(ColliderBase* collider);

    ColliderBase::List lists[7];
};
