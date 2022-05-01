#pragma once

#include "game/resource/resarchive.h"
#include "game/resource/resmgr.h"
#include "log.h"

static inline bool loadResource(const sead::SafeString& name, const sead::SafeString& path, bool isYaz0 = true) {
    bool validResource = ResMgr::instance()->loadRes(name, path, nullptr, isYaz0);
    if (!validResource) {
        LOG("%sFailed to load resource: %s (from file: %s)", LogColor::Red, name.cstr(), path.cstr());
        return false;
    }
    bool validArchiveRes = ResArchiveMgr::instance()->loadResArchive(name, path, nullptr);
    if (!validArchiveRes) {
        LOG("%sFailed to load archive resource: %s (from file: %s)", LogColor::Red, name.cstr(), path.cstr());
        return false;
    }
    return true;
}
