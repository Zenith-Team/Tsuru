#pragma once

#include "game/layout/layouthandler.h"

class LayoutContainer : public LayoutHandler { // Size: 0xE8C
public:
    LayoutContainer(LayoutAnimator* LayoutAnimatorArray, s32 LayoutAnimatorCount);
    virtual ~LayoutContainer();

    void getArchive(const sead::SafeString& name);
    void loadBFLYT(const sead::SafeString& name, u32 = 0, u32 = 0, u32 = 0);

    void* archiveAccessor;
};

static_assert(sizeof(LayoutContainer) == 0xE8C, "LayoutContainer size mismatch");
