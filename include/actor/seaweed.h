#pragma once

#include "actor/stageactor.h"

#include "model.h"

class Seaweed : public StageActor {
    SEAD_RTTI_OVERRIDE(Seaweed, StageActor)

public:
    Seaweed(const ActorBuildInfo* buildInfo);
    virtual ~Seaweed();

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;
    u32 onDelete() override;

    void setPlayerId(s8 id) override;

    CollisionMgr* getCollisionMgr() override;

    void vfAC() override;
    bool vfB4() override;
    void vfBC() override;
    void vfC4() override;
    void vfCC() override;

    void damageFromUnder() override;

    ModelWrapper* model;
    u8 unk1[8];
    u32 _288;
    u32 _28C;
};
