#pragma once

#include "game/effect/effect.h"
#include "game/graphics/model/model.h"
#include "game/actor/stage/multistateactor.h"

class PowerupBase : public MultiStateActor { // Size: 0x1A90
    SEAD_RTTI_OVERRIDE(PowerupBase, MultiStateActor)

public:
    enum PowerupState {
        PowerupState_Small       = 0,
        PowerupState_Big         = 1,
        PowerupState_Fire        = 2,
        PowerupState_Mini        = 3,
        PowerupState_Propeller   = 4,
        PowerupState_Penguin     = 5,
        PowerupState_Ice         = 6,
        PowerupState_Acorn       = 7,
        PowerupState_PAcorn      = 8
    };

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
    u32  vf12C() override;

    u32  vf13C() override;
    void vf144(bool unk) override;

    bool vf154() override;
    void move(Vec2f& dest) override;
    void setYSpeed(f32 ySpeed) override;
    u32  vf16C() override;
    u32  vf174() override;
    void getRect(Rect& rect) override;
    void doStateChange(StateBase* state) override;

    virtual void vf18C();                       // nullsub
    virtual void playBlockReleaseUpAnim();      // nullsub
    virtual void playBlockReleaseDownAnim();    // nullsub
    virtual void playIdleAnim();                // nullsub
    virtual void playFloatAnim();               // nullsub
    virtual void vf1B4();                       // nullsub
    virtual void vf1BC();
    // Player collision
    virtual u32  vf1C4();
    virtual void vf1CC();
    virtual void vf1D4();
    virtual void vf1DC();
    virtual void vf1E4();
    virtual void vf1EC();
    virtual void vf1F4();
    virtual void vf1FC();                       // nullsub
    virtual u32  vf204();
    DECLARE_STATE_VIRTUAL(PowerupBase, PowerupBaseState12); // unknown state
    DECLARE_STATE_VIRTUAL(PowerupBase, PowerupBaseState13); // unknown state
    DECLARE_STATE_VIRTUAL(PowerupBase, PowerupBaseState14); // unknown state
    DECLARE_STATE_VIRTUAL(PowerupBase, PowerupBaseState15); // unknown state
    DECLARE_STATE_VIRTUAL(PowerupBase, PowerupBaseState16); // unknown state
    DECLARE_STATE_VIRTUAL(PowerupBase, SpatByYoshi);

    DECLARE_STATE(PowerupBase, BlockReleaseUp);
    DECLARE_STATE(PowerupBase, BlockReleaseDown);
    DECLARE_STATE(PowerupBase, PowerupBaseState3);          // unknown state
    DECLARE_STATE(PowerupBase, RingRewardRelease);
    DECLARE_STATE(PowerupBase, PowerupBaseState5);          // unknown state
    DECLARE_STATE(PowerupBase, PowerupBaseState6);          // unknown state
    DECLARE_STATE(PowerupBase, PowerupBaseState7);          // unknown state
    DECLARE_STATE(PowerupBase, PowerupBaseState8);          // unknown state
    DECLARE_STATE(PowerupBase, PowerupBaseState9);          // unknown state
    DECLARE_STATE(PowerupBase, BeforeYoshiYongue);
    DECLARE_STATE(PowerupBase, InYoshiTongue);

    // Spawns the powerup in different ways depending on nybble 6
    void spawnMethod();
    // Spawns dust particles based on colliding tile type
    void spawnDustParticles();
    // Sets some physics and position values
    void setupActor();
    // Updates model animations and sets some position/rotation values on it
    void updateModel();
    // Yoshi eating related stuff
    void FUN_2518f94();
    // Sets this->_185F and this->_1828 to 0
    void FUN_25183ac();
    // Related to player collision (gives powerup state)
    // @param void* Unknown (Colliding player?)
    // @param setPowerupState Powerup state to set the colliding player to
    // @param u32 Unknown
    u32 FUN_25196e8(void*, PowerupState setPowerupState, u32);
    // Related to player collision (plays get sound?)
    u32 FUN_2519580(u32, u32);

    u8  unk1[8];
    u32 _17D0;
    u32 _17D4;
    u32 _17D8;
    u8  _17DC[36];
    ModelWrapper* model;
    TextureAnimation* texAnim;
    u32 _1808;
    u32 _180C;
    u32 _1810;
    u32 _1814;
    u32 _1818;
    u32 _181C;
    u32 _1820;
    u8  _1824;
    u8  _1825;
    u8  _1826;
    bool _1827;
    u8  _1828;
    u8  _1829;
    u8  _182A[2];
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
    u8  _185A;
    u8  unk4;
    u16 _185C;
    u8  _185E;
    u8  _185F;
    u8  _1860;
    u8  _1861;
    u8  _1862;
    u8  _1863;
    u8  _1864[52];
    f32 _1898;
    u8  _189C[4];
    u32 _18A0;
    PowerupBase* self;
    void* _18A8;
    HitboxCollider _18AC;
    u8  _19D4;
    u8  unk7[3];
    f32 _19D8;
    f32 _19DC;
    u32 _19E0;
    f32 _19E4;
    f32 _19E8;
    f32 _19EC;
    u32 _19F0;
    u8  _19F4;
    u8  unk8[3];
    u32 _19F8;
    u32 _19FC;
    u32 _1A00;
    EffectWrapper _1A04;
    u32 _1A6C;
    u8  _1A70;
    u8  _1A71;
    u8  unk9[2];
    u32 _1A74;
    u32 _1A78;
    u8  _1A7C;
    u8  _1A7D;
    u8  _1A7E;
    u8  _1A7F[0xD];
    void* _1A8C;
};
