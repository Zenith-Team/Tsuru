#pragma once

#include "game/actor/stage/stageactor.h"
#include "game/collision/actorphysicsmgr.h"

class PhysicsActor : public StageActor { // Size: 0x17A0
    SEAD_RTTI_OVERRIDE_DECL(PhysicsActor, StageActor);

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

    virtual void vf10C(u8);
    virtual u8 vf114();       // deleted
    virtual void vf11C();
    virtual void vf124(f32);
    virtual u32 vf12C();
    virtual void vf134();      // deleted
    virtual u32 vf13C();
    virtual void vf144(bool);
    virtual void vf14C(StageActor*);
    virtual bool vf154();
    // @param dest Destination position
    virtual void move(sead::Vector2f& dest);
    // @param ySpeed Target Y speed to be set to
    virtual void setYSpeed(f32 ySpeed);
    virtual u32 vf16C();
    virtual u32 vf174();
    virtual void getRect(sead::BoundBox2f& box) {
        box.set(
            this->position.x - 16.0f, this->position.y,
            this->position.x + 16.0f, this->position.y + 32.0f
        );
    }

    void handleGravity();
    void handleSpeed();

    inline void handlePhysics() {
        this->handleGravity();
        this->handleSpeed();
    }

    // Checks if ground below is suitable for walking. Useful for walking enemies
    // @param xOffset X offset of position to be evaluated
    // @param yOffset Y offset of position to be evaluated
    // @return Whether or not the ground below is suitable for walking
    inline bool checkForSuitableGround(f32 xOffset, f32 yOffset) {
        TileChecker::Param checkParam = { 0 };
        checkParam._2 = this->layer;
        checkParam._3 = this->collisionMask;

        TileChecker tileChecker(checkParam);

        sead::Vector2f a(this->position.x, this->position.y);
        sead::Vector2f b(this->position.x + xOffset, this->position.y + yOffset);

        return tileChecker.check(nullptr, a, b, 8);
    }

    u32 _27C;                           // 27C
    ActorPhysicsMgr physicsMgr;         // 280
    f32 _1760;                          // 1760 Inited to 0
    f32 _1764;                          // 1764 Inited to
    sead::Vector3f* _1768;              // 1768 Inited to &position
    u8 _176C;                           // 176C Inited to 0
    u8 _176D;                           // 176D Padding
    u8 _176E;                           // 176E Padding
    u8 _176F;                           // 176F Padding
    u32 _1770;                          // 1770 Inited to 0
    f32 _1774;                          // 1774 Inited to 1.0
    sead::Vector2f _1778;               // 1778 Inited to 0
    sead::Vector2f _1780;               // 1780 Inited to 0
    f32 maxYSpeed;                      // 1788 Inited to 1.5
    f32 minYSpeed;                      // 178C Inited to -1.5
    f32 _1790;                          // 1790 Inited to -0.0625
    u8 _1794;                           // 1794 Inited to 0
    u8 _1795;                           // 1795 Inited to 0
    u8 _1796;                           // 1796 Inited to 0
    u8 _1797;                           // 1797 Inited to 0
    u8 _1798;                           // 1798 Inited to 0
    u8 _1799;                           // 1799 Inited to 0
    u8 _179A;                           // 179A Inited to 0
    u8 _179B;                           // 179B Inited to 0
    u32 _179C;                          // 179C Inited to 0
};

static_assert(sizeof(PhysicsActor) == 0x17A0, "PhysicsActor size mismatch");
