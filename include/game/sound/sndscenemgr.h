#pragma once

#include "heap/seadDisposer.h"

class SndSceneMgr
{
    SEAD_SINGLETON_DISPOSER(SndSceneMgr);

public:
    bool loadSceneSound(u32 sceneId);
    bool loadData(u32 soundId);
    bool loadGameBgm(u32 bgmId);

    u32 prevSceneId;
    u32 sceneId;
    // ...
};
