#pragma once

#include "game/resource/resarchive.h"
#include "game/resource/resmgr.h"
#include "log.h"

static inline bool loadResource(const sead::SafeString& name, const sead::SafeString& path, bool isYaz0 = true, const char* requester = "*") {
    LOG("%s(TsuruResLoader:%s) Attemping to load resource %s", LogColor::Yellow, requester, path.cstr());
    bool validResource = ResMgr::instance()->loadRes(name, path, nullptr, isYaz0);
    if (!validResource) {
        LOG("%s(TsuruResLoader:%s) Failed to load resource %s", LogColor::Red, requester, path.cstr());
        return false;
    }
    if (ResArchiveMgr::instance()->get(name)) {
        LOG("%s(TsuruResLoader:%s) Resource %s is already loaded.", LogColor::LightGreen, requester, path.cstr());
        return true;
    }
    bool validArchiveRes = ResArchiveMgr::instance()->loadResArchive(name, name, nullptr);
    if (!validArchiveRes) {
        LOG("%s(TsuruResLoader:%s) Failed to load archive resource %s", LogColor::Red, requester, name.cstr());
        return false;
    }
    LOG("%s(TsuruResLoader:%s) Successfully loaded resource %s", LogColor::Green, requester, path.cstr());
    return true;
}
