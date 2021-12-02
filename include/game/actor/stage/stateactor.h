#pragma once

#include <game/states.h>
#include <game/actor/stage/physicsactor.h>

class StateActor : public PhysicsActor { // Size: 0x17C8
    SEAD_RTTI_OVERRIDE(StateActor, PhysicsActor)

public:
    StateActor(const ActorBuildInfo* buildInfo);
    virtual ~StateActor();

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
    void move(Vec2f& dest) override;
    void setYSpeed(f32) override;
    u32  vf16C() override;
    u32  vf174() override;
    void getRect(Rect& rect) override;

    StateWrapper<StateActor> states;    // 17A0
    u8 _17C4[4];                        // Unknown values
};
