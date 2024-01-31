#pragma once

#include "heap/seadDisposer.h"
#include "tiledatainfo.h"

class TileMgr { // Size: 0x9B88
    SEAD_SINGLETON_DISPOSER(TileMgr);

public:
    ENUM_CLASS(WaveType,
        None      = 0,
        Lava      = 1,
        Water     = 2,
        Poison    = 3,
        Quicksand = 4
    );

public:
    static u16* getTilePtr(u16 x, u16 y, u32 area, u8 layer, u32* blockIndexOut = nullptr);
    static u16* getTilePtrCurrentArea(u16 x, u16 y, u8 layer, u32* blockIndexOut = nullptr);

    TileDataInfo getTileData(u16 x, u16 y, u8 layer, bool withPSwitch = true);

    void* d_bgchk_data;
    f32 liquidTop;
    f32 liquidTop2;
    f32 waveFloats[1280];
    f32 waveFloats2[1280];
    u8 waveType;
    bool hasWaves;
    u8 _281E;
    u8 _281F;
    u32 liquidType;
    // TODO: I'll do this later, just copied Newer U for now
};
