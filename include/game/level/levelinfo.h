#pragma once

#include <sead.h>

class LevelInfo {
    SEAD_SINGLETON_DISPOSER(LevelInfo)

public:
    u8 mWorld;                   // 10
    u8 mLevel;                   // 11
    u8 mArea;                    // 12
    u8 mEntrance;                // 13
    u32 mZone;                   // 14
    u32 mEntranceType;           // 18
    u8 mDestWorld;               // 1C
    u8 mDestLevel;               // 1D
    u8 mDestArea;                // 1E
    u8 mDestEntrance;            // 1F
    u32 mDestZone;               // 20
    u32 mDestEntranceType;       // 24
};
