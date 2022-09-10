#pragma once

#include "game/actor/stage/stateactor.h"

class Boss;

class BossController : public StateActor { // Size: 0x17E0
    SEAD_RTTI_OVERRIDE(BossController, StateActor)

public:
    ENUM_CLASS(EndSequenceState,
        WaitingForBossDeath = 2
    );

public:
    BossController(const ActorBuildInfo* ActorBuildInfo);
    virtual ~BossController();

    u32 onCreate() override;

    u32 onExecute() override;
/*  //? No patience at the moment
    void setPlayerID(s8 id) override;

    void vfAC() override;
    bool vfB4() override;
    void vfBC() override;
    void vfC4() override;
    void vfCC() override;

    void damageFromUnder() override;

    void vf10C(u8) override;
    void vf11C() override;
    void vf124(f32) override;
    u32 vf12C() override;
    bool vf154() override;
    void move(Vec2f& dest) override;
    void setYSpeed(f32 ySpeed) override;
    u32 vf16C() override;
    u32 vf174() override;
    void getRect(Rect& rect) override;
*/
    DECLARE_STATE_VIRTUAL(BossController, Initialize);
    DECLARE_STATE_VIRTUAL(BossController, StartSequence);
    DECLARE_STATE_VIRTUAL(BossController, Wait);
    DECLARE_STATE_VIRTUAL(BossController, EndSequence);

    virtual void vf1E4();
    virtual void vf1EC();
    virtual u32 vf1F4();
    virtual u8 vf1FC();
    virtual u32 vf204();
    virtual Boss* getTargetBoss();
    virtual void spawnCutsceneKamek();
    virtual void vf21C();

    bool startSequenceFinished;
    u8 _17C9;
    u8 _17CA;
    bool bossDoneDying;
    u32 _17CC;
    EndSequenceState::__type__ endSequenceState;
    u32 _17D4;
    s32 startSequenceWaitTimer;
    u8 _17DC;
    u8 _17DD;
};

static_assert(sizeof(BossController) == 0x17E0, "BossController size mismatch");
