#pragma once

#include "terrain.h"

// TODO: verify

class Poison : public EnvTerrain {
public:
	u32 _11A78;
	u32 _11A7C;
};

class Water : public EnvTerrain {  // size: 0x11A88
public:
	f32 _11A78;		// 11A78
	u32 _11A7C;		// 11A7C
	u32 _11A80;		// 11A80
	u32 _11A84;		// 11A84
};
