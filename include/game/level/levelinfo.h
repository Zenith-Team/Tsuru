#pragma once

#include <sead.h>

class LevelInfo { // Size: 0x24
    SEAD_SINGLETON_DISPOSER(LevelInfo)

public:
    LevelInfo();

    // Sets the destination area to switch to
    // @param area Target area number
    void setDestArea(u8 area);
    // Sets the destination entrance to go to
    // @param entrance Target entrance number
    void setDestEntrance(s8 entrance);
    // Sets the destination level to switch to
    // @param level Target level number
    void setDestLevel(u8 level);
    // Sets the destination world to switch to
    // @param world Target world number
    void setDestWorld(u8 world);
    // Sets the destination zpne to switch to
    // @param zone Target zone number
    void setDestZone(u32 zone);

    // Sets destinations to the title screen level (1-39)
    void setTitlescreenDestination();

    // Custom function
    void setTitlescreenThemeEntrance();

    u8 world;                   // 10
    u8 level;                   // 11
    u8 area;                    // 12
    s8 entrance;                // 13
    u32 zone;                   // 14
    u32 entranceType;           // 18
    u8 destWorld;               // 1C
    u8 destLevel;               // 1D
    u8 destArea;                // 1E
    u8 destEntrance;            // 1F
    u32 destZone;               // 20
//  u32 destEntranceType;       // 24
};

static_assert(sizeof(LevelInfo) == 0x24, "LevelInfo size mismatch");
