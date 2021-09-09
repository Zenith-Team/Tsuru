#pragma once

#include <game/actor/stage/powerupbase.h>

class Powerup : public PowerupBase { // Size: 0x1A98
    SEAD_RTTI_OVERRIDE(Powerup, PowerupBase)

public:
    Powerup(const ActorBuildInfo* buildInfo);
    virtual ~Powerup();

    void setPlayerID(s8 id) override;

    ActorPhysicsMgr* getActorPhysicsMgr() override;
    void vfAC() override;
    bool vfB4() override;
    void vfBC() override;
    void vfC4() override;
    void vfCC() override;

    void damageFromUnder() override;
    void vf10C(u8 unk) override;
    
    void vf11C() override;
    void vf124(f32 unk) override;
    u32  vf12C() override;
    
    u32  vf13C() override;

    bool vf154() override;
    void move(Vec2f& dest) override;
    void setYSpeed(f32 ySpeed) override;
    u32  vf16C() override;
    u32  vf174() override;
    void getRect(Rect& rect) override;
    void doStateChange(StateBase* state) override;
    void vf18C() override;                      // nullsub
    void playBlockReleaseUpAnim() override;     // nullsub
    void playBlockReleaseDownAnim() override;   // nullsub
    void playIdleAnim() override;               // nullsub
    void playFloatAnim() override;              // nullsub
    void vf1B4() override;                      // nullsub

    u32  vf1C4() override;

    void vf1FC() override;

    virtual void vf29C();                       // nullsub
    virtual void vf2A4();                       // nullsub
    virtual void vf2AC();

    DECLARE_STATE(Powerup, PowerupState1);  // unknown state
    DECLARE_STATE(Powerup, PowerupState2);  // unknown state
    DECLARE_STATE(Powerup, PowerupState3);  // unknown state
    DECLARE_STATE(Powerup, PowerupState4);  // unknown state

    u8 _1A90;    // _1A90
    u8 _1A91;    // _1A91
    u8 _1A92[6]; // _1A92
};
