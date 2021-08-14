#pragma once

#include <types.h>

class CheatMgr {
public:
    CheatMgr();

    static CheatMgr sInstance;

    bool mInfiniteLivesEnabled;     // _0
    bool mInfiniteTimeEnabled;      // _1
    bool mNoClipEnabled;            // _2
    bool mInvincibilityEnabled;     // _3
    bool mCollisionViewerEnabled;   // _4
    bool mDebugLoggingEnabled;      // _5
    bool mAntiAliasingEnabled;      // _6
    bool mQuickRespawnEnabled;      // _7
};
