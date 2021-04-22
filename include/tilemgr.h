#pragma once

#include "types.h"
#include "tiles.h"


class TileMgr {
public:
    static TileMgr* instance;

    // TODO: verify
    void *d_bgchk_data;		
	float liquidTop;		
	float liquidTop2;		
	float waveFloats[1280];		
	float waveFloats2[1280];		
	u8 waveType;		
	u8 hasWaves;		
	u8 _281E;		
	u8 _281F;		
	u32 liquidType;

    static u16* getTilePtr(u16 x, u16 y, u32 area, u8 layer, u32* blockIndexOut = nullptr);
    static u16* getTilePtrCurrentArea(u16 x, u16 y, u8 layer, u32* blockIndexOut = nullptr);
};
