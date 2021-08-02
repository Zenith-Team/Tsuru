#pragma once

#include "game/effect/effect.h"
#include "game/graphics/model/model.h"
#include "game/actor/stage/multistateactor.h"

class PowerupBase : public MultiStateActor { // Size: 0x1a90
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

    void spawnMethod(); // Spawns the powerup in different ways depending on nybble 6
    void spawnDustParticles();  // Spawns dust particles based on colliding tile type

    u8 unk1[8];
    u32 _17D0;
    u32 _17D4;
    u32 _17D8;
    u8 unk2[36];
    ModelWrapper* mModel;
    u8 unk3[4];
    u32 _1808;
    u32 _180C;
    u32 _1810;
    u32 _1814;
    u32 _1818;
    u32 _181C;
    u32 _1820;
    u8 _1824;
    u8 _1825;
    u8 _1826;
    u8 _1827;
    u8 _1828;
    u8 _1829;
    u8 unk4[2];
    u32 _182C;
    s32 _1830;
    u32 _1834;
    u32 _1838;
    u32 _183C;
    u32 _1840;
    u32 _1844;
    u32 _1848;
    u32 _184C;
    u32 _1850;
    u32 _1854;
    u16 _1858;
    u8 _185A;
    u8 unk5;
    u16 _185C;
    u8 _185E;
    u8 _185F;
    u8 _1860;
    u8 _1861;
    u8 _1862;
    u8 _1863;
    u8 unk6[52];
    f32 _1898;
    u8 unk7[4];
    u32 _18A0;
    PowerupBase* _18A4;
    void* _18A8;
    HitboxCollider mHitboxCollider;
    u8 _19D4;
    u8 unk8[3];
    f32 _19D8;
    f32 _19DC;
    u32 _19E0;
    f32 _19E4;
    f32 _19E8;
    f32 _19EC;
    u32 _19F0;
    u8 _19F4;
    u8 unk9[3];
    u32 _19F8;
    u32 _19FC;
    u32 _1A00;
    EffectWrapper mEffectWrapper;
    u32 _1A6C;
    u8 _1A70;
    u8 _1A71;
    u8 unk10[2];
    u32 _1A74;
    u32 _1A78;
    u8 _1A7C;
    u8 _1A7D;
    u8 _1A7E;
    u8 unk11[13];
    void* _1A8C;
};
