#pragma once

#include <types.h>

void mapPositionToScreen(Vec2f& out, const Vec2f& position);

bool moveValueTo(u32* value, u32 target, u32 amount);
bool moveFloatTo(f32* value, f32 target, f32 amount);
