#pragma once

#include "actor/physicsactor.h"

#include "effect.h"
#include "lightsource.h"

class BowserFireball : public PhysicsActor {  // size: 0x1888
    SEAD_RTTI_OVERRIDE(BowserFireball, PhysicsActor)

public:
    BowserFireball(const ActorBuildInfo* buildInfo);
    virtual ~BowserFireball();

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void setPlayerId(s8 id) override;

    CollisionMgr* getCollisionMgr() override;

    void vfAC() override;

    bool vfB4() override;

    void vfBC() override;
    void vfC4() override;
    void vfCC() override;

    void damageFromUnder() override;

    void vf10C(u8 unk) override;

    void vf11C() override;
    void vf124(f32) override;

    u32 vf12C() override;

    bool vf154() override;

    void move(Vec2& dest) override;
    void setYSpeed(f32 ySpeed) override;

    u32 vf16C() override;
    u32 vf174() override;

    void getRect(Rect& rect) override;

    EffectWrapper effectWrapper;    // 17C8     
    LightSource lightSource;        // 1830     
    u32 _1878;                      // 1878     // TODO: check signage
    u32 _187C;                      // 187C     //* if nyyble 12 is 0 then this is 0x1E, otherwise it is 0
    void* _1880;                    // 1880     
    u32 _1884;                      // 1884     //* probably unused
};
