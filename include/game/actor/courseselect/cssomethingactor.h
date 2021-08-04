#pragma once

#include "game/actor/courseselect/csactor.h"

class CSSomethingActor : public CSActor {
    SEAD_RTTI_OVERRIDE(CSSomethingActor, CSActor)

public:
    CSSomethingActor(const ActorBuildInfo* buildInfo);
    virtual ~CSSomethingActor();

    bool vf8C() override;
    void vf94() override;
    void vf9C() override;
    void vfA4() override;

    s32 _108;   // Inited to -1
};
