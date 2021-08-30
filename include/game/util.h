#pragma once

#include <types.h>

void mapPositionToScreen(Vec2f& out, const Vec2f& position);

bool moveValueTo(u32& out, u32 target, u32 step);
bool moveFloatTo(f32& out, f32 target, f32 step);
