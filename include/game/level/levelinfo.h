#pragma once

#include <sead.h>

class LevelInfo {
    SEAD_SINGLETON_DISPOSER(LevelInfo)

public:
    u8 world;                   // 10
    u8 level;                   // 11
    u8 area;                    // 12
    u8 entrance;                // 13
    u32 zone;                   // 14
    u32 entranceType;           // 18
    u8 destWorld;               // 1C
    u8 destLevel;               // 1D
    u8 destArea;                // 1E
    u8 destEntrance;            // 1F
    u32 destZone;               // 20
    u32 destEntranceType;       // 24
};
