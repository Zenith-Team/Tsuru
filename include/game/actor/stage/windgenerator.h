#pragma once

#include "game/actor/stage/stageactor.h"

class WindGenerator : public StageActor { // Size: 0x2A0
    SEAD_RTTI_OVERRIDE_DECL(WindGenerator, StageActor);

public:
    inline WindGenerator(const ActorBuildInfo* buildInfo) : StageActor(buildInfo) { }
    virtual ~WindGenerator();

    u32 onCreate() override;

    u32 onExecute() override;

    void setPlayerID(s8 id) override;

    ActorPhysicsMgr* getActorPhysicsMgr() override;
    void vfAC() override;
    bool vfB4() override;
    void vfBC() override;
    void vfC4() override;
    void vfCC() override;

    void damageFromUnder() override;

    f32 finalWindStrength;      // 27C
    f32 windStrength;           // 280
    f32 _284;                   // 284
    f32 _288;                   // 288
    u8  _28C[4];                // 28C
    u32 _290;                   // 290
    u32 _294;                   // 294
    u32 _298;                   // 298
    u32 _29C;                   // 29C
};
