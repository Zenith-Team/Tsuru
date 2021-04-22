#pragma once

#include "terrain.h"

// TODO: verify

class Poison : public EnvTerrain {
public:
	u32 _11A78;
	u32 _11A7C;
};

class Water : public EnvTerrain {
public:
	float _11A78;
	u32 _11A7C;
	u32 _11A80;
	u32 _11A84;
};
