#pragma once

#include "model.h"
#include "terrain.h"

// TODO: verify

class Lava : public EnvTerrain {  // size: 0x11a88
public:
	u8 unk1[8];				// 11A78	//? unknown values 1
	ModelWrapper* model;	// 11A80  
	u8 unk2[4];				// 11A84 	//? unknown values 2
};

class Poison : public EnvTerrain {
public:
	u32 _11A78;
	u32 _11A7C;
};

class Water : public EnvTerrain {  // size: 0x11a88
public:
	f32 _11A78;		// 11A78
	u32 _11A7C;		// 11A7C
	u32 _11A80;		// 11A80
	u32 _11A84;		// 11A84
};
