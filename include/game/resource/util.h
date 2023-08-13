#pragma once

#include "game/resource/resarchive.h"
#include "game/resource/resmgr.h"
#include "log.h"

static inline bool loadResource(const sead::SafeString& name, const sead::SafeString& path, bool isYaz0 = true, const char* requester = "*") {
    PRINT(LogColor::Yellow, "TsuruResLoader: ", requester, " is attempting to load resource: ", path.cstr());
    bool validResource = ResMgr::instance()->loadArchiveRes(name, path, nullptr, isYaz0);
    if (!validResource) {
        PRINT(LogColor::Red, "TsuruResLoader: ", requester, " failed to load resource: ", path.cstr());
        return false;
    }

    if (ResArchiveMgr::instance()->get(name)) {
        PRINT(LogColor::Yellow, "TsuruResLoader: ", requester, " resource already loaded: ", path.cstr());
        return true;
    }

    bool validArchiveRes = ResArchiveMgr::instance()->loadResArchive(name, name, nullptr);
    if (!validArchiveRes) {
        PRINT(LogColor::Red, "TsuruResLoader: ", requester, " failed to load archive resource: ", path.cstr());
        return false;
    }

    PRINT(LogColor::Green, "TsuruResLoader: ", requester, " successfully loaded resource: ", path.cstr());
    return true;
}
