#pragma once

#include "game/states.h"
#include "game/collision/cshitboxcollider.h"
#include "game/actor/courseselect/csactor.h"

class CSCollisionActor : public CSActor {
    SEAD_RTTI_OVERRIDE(CSCollisionActor, CSActor)

public:
    CSCollisionActor(const ActorBuildInfo* buildInfo);
    virtual ~CSCollisionActor();

    virtual bool vf8C();
    virtual void vf94();
    virtual void vf9C();
    virtual void vfA4(); // nullsub
    virtual void vfAC(); // nullsub
    virtual u32 vfB4();
    virtual u32 vfBC();
    virtual void vfC4(f64, Vec3f*);
    virtual void vfCC(); // nullsub
    virtual u32 vfD4();
    virtual void vfDC();
    virtual u8 vfE4();
    virtual u8 vfEC();
    virtual void vfF4(Vec3f* position); // Player collision related? (spawns effect RP_CSelect_HitNormal)
    virtual void vfFC();
    virtual void vf104(u32);
    virtual void vf10C();
    virtual void vf114();   // Death related? (spawns effect RP_CSelect_EnemyBurst)
    virtual void vf11C();
    virtual void vf124();

    StateWrapper<CSCollisionActor> mStates;
    u8 _12C[0x18];  // Unknown struct
    CSHitboxCollider mHitbox;
    u32 mLinkID;
    u32 _164;
    u32 _168;
    s32 _16C;
    u8 _170;
    u8 _171;
    u8 _172;
};
