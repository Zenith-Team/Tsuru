#pragma once

#include "enemy.h"

// TODO: methods, members, verify

class Bobomb : public Enemy {
public:
    Bobomb(const ActorBuildInfo* buildInfo);
    virtual ~Bobomb();

    bool checkDerivedRuntimeTypeInfo(void*);

    u32 onCreate() override;

    u32 beforeExecute() override;
    u32 onExecute() override;

    u32 onDraw() override;

    u32 onDelete() override;

    //...
};
