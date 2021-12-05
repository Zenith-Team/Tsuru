#pragma once

#include "courseselectactor.h"
#include "game/effect/effect.h"

class CSPlayerBase : public CourseSelectActor {
    SEAD_RTTI_OVERRIDE(CSPlayerBase, CourseSelectActor)

public:
    CSPlayerBase(const ActorBuildInfo* buildInfo);
    virtual ~CSPlayerBase();

    u32 onCreate() override = 0;

    u32 onExecute() override = 0;

    u32 onDraw() override = 0;

    bool vf8C() override;
    void vf94() override;
    void vf9C() override;
    void onCSScriptCommandUpdate() override;

    virtual void vfAC() = 0;
    virtual void vfB4() = 0;
    virtual void vfBC() = 0;
    virtual void vfC4() = 0;
    virtual void vfCC() = 0;
    virtual void vfD4() = 0;
    virtual u32 vfDC();
    virtual void vfE4();
    virtual void vfEC();
    virtual u32 vfF4();
    virtual void vfFC();    // deleted
    virtual void vf104();   // deleted
    virtual void vf10C();   // deleted
    virtual void vf114() = 0;
    virtual void vf11C() = 0;

    u32 _108;
    u32 _10C;
    u32 _110;
    u32 _114;
    u8 _118;
    u32 _11C;
    u32 _120;
    f32 _124;
    f32 _128;
    u32 _12C;
    u32 _130;
    u32 _134;
    u32 _138;
    s32 _13C;
    s32 _140;
    s32 _144;
    u8 _148;
    f32 _14C;
    u32 _150;
    u32 _154;
    u32 _158;
    u32 _15C;
    f32 _160;
    f32 _164;
    Vec3f _168;
    Vec3f _174;
    u32 _180;
    u32 _184;
    u32 _188;
    f32 _18C;
    u32 _190;
    u32 _194;
    u32 _198;
    u32 _19C;
    u32 _1A0;
    u32 _1A4;
    u32 _1A8;
    u32 _1AC;
    s32 _1B0;
    u32 _1B4;
    u16 _1B8;
    EffectWrapper _1BC;
    u32 _224;
    u8 _228;
    u8 _229;
    EffectWrapper _22C;
    u32 _294;
    u8 _298;
    EffectWrapper _29C;
    u32 _304;
    u8 _308;
    EffectWrapper _30C;
};

static_assert(sizeof(CSPlayerBase) == 0x374, "CSPlayerBase size mismatch");
