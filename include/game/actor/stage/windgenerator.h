#pragma once

#include <game/actor/stage/stageactor.h>

class WindGenerator : public StageActor { // Size: 0x2A0
    SEAD_RTTI_OVERRIDE(WindGenerator, StageActor)

public:
    // TODO: maybe this isn't the best way of doing this... (the ctor is inlined in the build function)
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

    f32 finalWindStrength;      // _27C
    f32 windStrength;           // _280
    f32 _284;                   // _284
    f32 _288;                   // _288
    u8  _28C[4];                // _28C
    u32 _290;                   // _290
    u32 _294;                   // _294
    u32 _298;                   // _298
    u32 _29C;                   // _29C
};
