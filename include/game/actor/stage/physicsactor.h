#pragma once

#include <game/actor/stage/stageactor.h>
#include <game/collision/actorphysicsmgr.h>

class PhysicsActor : public StageActor { // size: 0x17A0
    SEAD_RTTI_OVERRIDE(PhysicsActor, StageActor)

public:
    PhysicsActor(const ActorBuildInfo* buildInfo);
    virtual ~PhysicsActor();

    void afterCreate(u32) override;

    u32 beforeExecute() override;
    void afterExecute(u32) override;

    u32 onDelete() override;

    void setPlayerID(s8 id) override;

    ActorPhysicsMgr* getActorPhysicsMgr() override;
    void vfAC() override;
    bool vfB4() override;
    void vfBC() override;
    void vfC4() override;
    void vfCC() override;

    void damageFromUnder() override;

    virtual void vf10C(u8 unk);
    virtual u8 vf114();       // deleted
    virtual void vf11C();
    virtual void vf124(f32 unk);
    virtual u32 vf12C();
    virtual void vf134();      // deleted
    virtual u32 vf13C();
    virtual void vf144(bool unk);
    virtual void vf14C(StageActor* unk);
    virtual bool vf154();
    virtual void move(Vec2f& dest);
    virtual void setYSpeed(f32 ySpeed);
    virtual u32 vf16C();
    virtual u32 vf174();
    virtual void getRect(Rect& rect);

    void handleGravity();
    void handleSpeed();

    inline bool checkForSuitableGround(f32 xOffset, f32 yOffset) {
        TileChecker::Param checkParam = { 0 };
        checkParam._2 = this->layer;
        checkParam._3 = this->collisionMask;

        TileChecker tileChecker(checkParam);

        Vec2f a(this->position.x, this->position.y);
        Vec2f b(this->position.x + xOffset, this->position.y + yOffset);

        return tileChecker.check(nullptr, a, b, 8);
    }

    u32 _27C;                           // _27C
    ActorPhysicsMgr physicsMgr;         // _280
    f32 _1760;                          // _1760 Inited to 0
    f32 _1764;                          // _1764 Inited to
    Vec3f* _1768;                       // _1768 Inited to &position
    u8 _176C;                           // _176C Inited to 0
    u8 _176D;                           // _176D Padding
    u8 _176E;                           // _176E Padding
    u8 _176F;                           // _176F Padding
    u32 _1770;                          // _1770 Inited to 0
    f32 _1774;                          // _1774 Inited to 1.0
    Vec2f _1778;                        // _1778 Inited to 0
    Vec2f _1780;                        // _1780 Inited to 0
    f32 maxYSpeed;                      // _1788 Inited to 1.5
    f32 minYSpeed;                      // _178C Inited to -1.5
    f32 _1790;                          // _1790 Inited to -0.0625
    u8 _1794;                           // _1794 Inited to 0
    u8 _1795;                           // _1795 Inited to 0
    u8 _1796;                           // _1796 Inited to 0
    u8 _1797;                           // _1797 Inited to 0
    u8 _1798;                           // _1798 Inited to 0
    u8 _1799;                           // _1799 Inited to 0
    u8 _179A;                           // _179A Inited to 0
    u8 _179B;                           // _179B Inited to 0
    u32 _179C;                          // _179C Inited to 0
};
