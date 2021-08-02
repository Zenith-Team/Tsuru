#pragma once

#include "game/actor/stage/powerupbase.h"

class Powerup : PowerupBase { // Size: 0x1a98
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
    u32 vf12C() override;
    
    u32 vf13C() override;

    bool vf154() override;
    void move(Vec2f& dest) override;
    void setYSpeed(f32 ySpeed) override;
    u32 vf16C() override;
    u32 vf174() override;
    void getRect(Rect& rect) override;
    void doStateChange(StateBase* state) override;
    void vf18C() override; // nullsub
    void vf194() override; // nullsub
    void vf19C() override; // nullsub
    void vf1A4() override; // nullsub
    void vf1AC() override; // nullsub
    void vf1B4() override; // nullsub

    u32 vf1C4() override;

    void vf1FC() override;

    DECLARE_STATE_VIRTUAL(PowerupBase, Unk18);

    u8 _1A90;   // _1A90
    u8 _1A91;   // _1A91
    u8 unk1[6]; // _1A92
};
