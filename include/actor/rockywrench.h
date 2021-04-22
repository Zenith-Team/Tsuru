#pragma once

#include "enemy.h"

// TODO: methods, members, verify

class RockyWrench : public Enemy { // size: 0x
public:
    RockyWrench(const ActorBuildInfo* buildInfo);
    virtual ~RockyWrench();

    bool checkDerivedRuntimeTypeInfo(void*);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    //? some functions here

    void vf10C(u8 unk) override;

    void vf11C() override;
    void vf124(f32) override;

    u32 vf12C() override;

    void move(Vec2& dest) override;
    void setYSpeed(f32 ySpeed) override;
    
    u32 vf16C() override;
    u32 vf174() override;

    void getRect(Rect& rect) override;

    // ...
};
