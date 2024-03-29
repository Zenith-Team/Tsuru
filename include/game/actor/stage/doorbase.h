#pragma once

#include "game/actor/stage/enemy.h"
#include "game/graphics/model/modelnw.h"

class DoorBase : public Enemy { // Size: 0x18A8
    SEAD_RTTI_OVERRIDE_DECL(DoorBase, Enemy);

public:
    DoorBase(const ActorBuildInfo* buildInfo);
    virtual ~DoorBase();

    u32 onCreate() override;

    u32 onExecute() override;

    u32 onDraw() override;

    void vf18C() override; // nullsub

    virtual void vf4E4(); // deleted
    virtual void ZOrder();
    DECLARE_STATE_VIRTUAL(DoorBase, DoorBaseState1);
    DECLARE_STATE_VIRTUAL(DoorBase, DoorBaseState2);
    DECLARE_STATE_VIRTUAL(DoorBase, DoorBaseState3);
    DECLARE_STATE_VIRTUAL(DoorBase, DoorBaseState4);
    virtual bool isCurrentStateDoorBaseState3();
    virtual u32  vf55C(); // nullsub
    virtual void vf564(); // deleted
    virtual void vf56C(); // deleted
    virtual void loadModel();
    virtual void initHitboxCollider();
    virtual void vf584(); // nullsub
    virtual void vf58C(); // nullsub
    virtual void playOpenDoorAnim();
    virtual void playOpenDoorSound();
    virtual void playCloseDoorAnim();
    virtual void playCloseDoorSound();
    virtual void vf5B4(); // nullsub
    virtual void vf5BC();
    virtual u32  vf5C4(); // nullsub

    static void collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther);

    ModelWrapper* model;
    u32  _1884;
    u32  _1888;
    u32  _188C;
    u32  _1890;
    u32  _1894;
    bool _1898;
    u32  _189C;
    u32  _18A0;
    s32  _18A4;
};

static_assert(sizeof(DoorBase) == 0x18A8, "DoorBase size mismatch");
