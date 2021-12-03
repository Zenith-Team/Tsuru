#pragma once

#include <game/states.h>
#include <game/actor/stage/physicsactor.h>

class MultiStateActor : public PhysicsActor { // Size: 0x17C8
    SEAD_RTTI_OVERRIDE(MultiStateActor, PhysicsActor)

public:
    MultiStateActor(const ActorBuildInfo* buildInfo);
    virtual ~MultiStateActor();

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
    void vf124(f32) override;
    u32  vf12C() override;

    bool vf154() override;
    void move(sead::Vec2f& dest) override;
    void setYSpeed(f32) override;
    u32  vf16C() override;
    u32  vf174() override;
    void getRect(Rect& rect) override;

    // Changes the current state to a new target state
    // @param state Pointer to target state
    virtual void doStateChange(StateBase* state);

    MultiStateWrapper<MultiStateActor> states; // 17A0
};
