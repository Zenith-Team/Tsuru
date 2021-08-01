#pragma once

#include "game/actor/stage/multistateactor.h"

class PowerupBase : public MultiStateActor {
    SEAD_RTTI_OVERRIDE(PowerupBase, MultiStateActor)

public:
    PowerupBase(const ActorBuildInfo* buildInfo);
    virtual ~PowerupBase();

    u32 onDraw() override;

    void setPlayerID(s8 id) override;

    ActorPhysicsMgr* getActorPhysicsMgr() override;
    void vfAC() override;
    bool vfB4() override;
    void vfBC() override;
    void vfC4() override;
    void vfCC() override;
    void killAtGoal() override;
    void splashWater(Vec3f*) override;
    void splashLava(Vec3f*) override;
    void splashLavaWave(Vec3f*) override;
    void splashPoison(Vec3f*) override;

    void damageFromUnder() override;

    void vf10C(u8 unk) override;

    void vf10C(u8 unk);
    
    void vf11C() override;
    void vf124(f32 unk) override;
    u32 vf12C() override;
    
    u32 vf13C() override;
    void vf144(bool unk) override;

    bool vf154() override;
    void move(Vec2f& dest) override;
    void setYSpeed(f32 ySpeed) override;
    u32 vf16C() override;
    u32 vf174() override;
    void getRect(Rect& rect) override;
    void doStateChange(StateBase* state) override;

    virtual void vf18C(); // nullsub
    virtual void vf194(); // nullsub
    virtual void vf19C(); // nullsub
    virtual void vf1A4(); // nullsub
    virtual void vf1AC(); // nullsub
    virtual void vf1B4(); // nullsub
    virtual void vf1BC();
    virtual u32 vf1C4();
    virtual void vf1CC();
    virtual void vf1D4();
    virtual void vf1DC();
    virtual void vf1E4();
    virtual void vf1EC();
    virtual void vf1F4();
    virtual void vf1FC(); // nullsub
    virtual u32 vf204();
    DECLARE_STATE_VIRTUAL(PowerupBase, Unk12);
    DECLARE_STATE_VIRTUAL(PowerupBase, Unk13);
    DECLARE_STATE_VIRTUAL(PowerupBase, Unk14);
    DECLARE_STATE_VIRTUAL(PowerupBase, Unk15);
    DECLARE_STATE_VIRTUAL(PowerupBase, Unk16);
    DECLARE_STATE_VIRTUAL(PowerupBase, SpatByYoshi);

    void spawnMethod(); // Spawns the powerup in different ways depending nybble 6
    void spawnDustParticles();  // Spawns dust particles based on colliding tile type
};
