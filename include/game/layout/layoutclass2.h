#pragma once

#include "game/layout/layoutclass1.h"

class LayoutClass2 : public LayoutClass1 { // Size: 0xE8C
public:
    LayoutClass2(CoLayout*, s32);
    virtual ~LayoutClass2();

    void getArchive(const sead::SafeString& name);
    void loadBFLYT(const sead::SafeString& name, u32 = 0, u32 = 0, u32 = 0);

    void* _E88;
};

static_assert(sizeof(LayoutClass2) == 0xE8C, "LayoutClass2 size mismatch");
