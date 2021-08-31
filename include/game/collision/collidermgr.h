#pragma once

#include <game/collision/solid/colliderbase.h>

class ColliderMgr : public sead::IDisposer {
public:
    void add(ColliderBase* collider);
    void remove(ColliderBase* collider);

    static ColliderMgr* instance() { return sInstance; }

protected:
    static ColliderMgr* sInstance;

public:
    ColliderBase::List mLists[7];
};
