#pragma once

#include "sead/idisposer.h"

class TileMgr { // Size: 0x9B88
    SEAD_SINGLETON_DISPOSER(TileMgr)

public:
	enum WaveType {
		WaveType_None 	   = 0,
		WaveType_Lava 	   = 1,
		WaveType_Water 	   = 2,
		WaveType_Poison    = 3,
		WaveType_Quicksand = 4
	};

public:
	void* d_bgchk_data;
	f32 liquidTop;
	f32 liquidTop2;
	f32 waveFloats[0x500][2];
	u8 waveType;
	bool hasWaves;
	u8 _281E;
	u8 _281F;
	u32 liquidType;
    // TODO: I'll do this later, just copied Newer U for now
};
