#pragma once

#include "sead/idisposer.h"
#include "sead/safestring.h"

class ResMgr {
    SEAD_SINGLETON_DISPOSER(ResMgr);

public:
    ResMgr();

    bool loadRes(const sead::SafeString& resName, const sead::SafeString& filePath, sead::Heap* heap, bool isYaz0);
};
