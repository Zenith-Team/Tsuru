#pragma once

#include "actor/stageactor.h"

#include "model.h"

class Seaweed : public StageActor {  // size: 0x290
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

    ModelWrapper* model;    // 27C
    u8 unk1[8];             // 280
    u32 _288;               // 288
    u32 _28C;               // 28C
};
