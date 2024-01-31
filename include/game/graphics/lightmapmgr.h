#pragma once

#include "framework/seadCalculateTask.h"
#include "framework/seadTaskMgr.h"
#include "lighting/aglLightMapMgr.h"

class LightMapMgr : public sead::CalculateTask { // Size: 0x52CC
    SEAD_TASK_SINGLETON_DISPOSER(LightMapMgr);

public:
    static const u32 cLightMapNum = 2;

    void setCSLightMaps(u32 = 0);

    u8 _CC[0x2070 - 0xCC];
    agl::lght::LightMapMgr agllmap;
    u8 _4DDC[0x52C8 - 0x4DDC];
    bool isInitialized;
};

static_assert(sizeof(LightMapMgr) == 0x52CC, "LightMapMgr size mismatch");
