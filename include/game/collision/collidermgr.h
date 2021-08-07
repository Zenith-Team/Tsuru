#pragma once

#include <game/collision/solid/colliderbase.h>

class ColliderMgr : public sead::IDisposer {
public:
    void add(ColliderBase* collider);
    void remove(ColliderBase* collider);

    static ColliderMgr* sInstance;

    ColliderBase::List mLists[7];
};
