#pragma once

#include <types.h>

class CheatMgr {
public:
    CheatMgr();

    static inline void toggleInfiniteLives() {
        if (CheatMgr::sInstance.mInfiniteLivesEnabled)
            CheatMgr::sInstance.mInfiniteLivesEnabled = false;
        else
            CheatMgr::sInstance.mInfiniteLivesEnabled = true;
    }

    static inline void toggleInfiniteTime() {
        if (CheatMgr::sInstance.mInfiniteTimeEnabled)
            CheatMgr::sInstance.mInfiniteTimeEnabled = false;
        else
            CheatMgr::sInstance.mInfiniteTimeEnabled = true;
    }

    static inline void toggleNoClip() {
        if (CheatMgr::sInstance.mNoClipEnabled)
            CheatMgr::sInstance.mNoClipEnabled = false;
        else
            CheatMgr::sInstance.mNoClipEnabled = true;
    }

    static inline void toggleInvincibility() {
        if (CheatMgr::sInstance.mInvincibilityEnabled)
            CheatMgr::sInstance.mInvincibilityEnabled = false;
        else
            CheatMgr::sInstance.mInvincibilityEnabled = true;
    }

    static inline void toggleCollisionViewer() {
        if (CheatMgr::sInstance.mCollisionViewerEnabled)
            CheatMgr::sInstance.mCollisionViewerEnabled = false;
        else
            CheatMgr::sInstance.mCollisionViewerEnabled = true;
    }

    static inline void toggleDebugLogging() {
        if (CheatMgr::sInstance.mDebugLoggingEnabled)
            CheatMgr::sInstance.mDebugLoggingEnabled = false;
        else
            CheatMgr::sInstance.mDebugLoggingEnabled = true;
    }

    static inline void toggleAntiAliasing() {
        if (CheatMgr::sInstance.mAntiAliasingEnabled)
            CheatMgr::sInstance.mAntiAliasingEnabled = false;
        else
            CheatMgr::sInstance.mAntiAliasingEnabled = true;
    }

    static inline void toggleQuickRespawn() {
        if (CheatMgr::sInstance.mQuickRespawnEnabled)
            CheatMgr::sInstance.mQuickRespawnEnabled = false;
        else
            CheatMgr::sInstance.mQuickRespawnEnabled = true;
    }

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
