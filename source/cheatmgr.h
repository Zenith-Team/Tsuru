#pragma once

#include <types.h>

class CheatMgr {
public:
    CheatMgr();

    static CheatMgr* sInstance;

    bool mInfiniteLivesEnabled;
    bool mInfiniteTimeEnabled;
    bool mNoClipEnabled;
    bool mInvincibilityEnabled;
    bool mCollisionViewerEnabled;
    bool mDebugLoggingEnabled;
};
