#pragma once

#include "types.h"

class PlayerLookTarget : public sead::IDisposer {  // size: 0x2C
public:
	u32 ownerId;	// 10
	Vec2 _14;		// 14
	u32 _1C;		// 1C
	u32 _20;		// 20
	u32 _24;		// 24
	u32 _28;		// 28
};

void mapPosToScreen(Vec2* , Vec2* );
bool moveValueTo(u32*, u32 target, u32 amount);	
bool moveFloatTo(f32*, f32 target, f32 amount);
