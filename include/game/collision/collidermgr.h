#pragma once

#include "game/collision/solid/colliderbase.h"

class ColliderMgr {
    SEAD_SINGLETON_DISPOSER(ColliderMgr)

public:
    // Adds a collider to the lists
    // @param collider Pointer to collider to be added
    void add(ColliderBase* collider);
    // Removes a collider from the lists
    // @param collider Pointer to collider to be removed
    void remove(ColliderBase* collider);

    ColliderBase::List lists[7];
};
