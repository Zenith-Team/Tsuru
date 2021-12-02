#pragma once

#include "types.h"

// Maps a position to the screen
// @param out Output Vec2f variable
// @param position Position to be mapped
void mapPositionToScreen(Vec2f& out, const Vec2f& position);

// Smoothly moves an integer variable towards a target value
// @param out Reference to variable which will be modified
// @param target The value to move the variable towards
// @param step The amount that the variable will be moved by
// @return Whether or not the variable has reached the target
bool moveValueTo(u32& out, u32 target, u32 step);

// Smoothly moves a float variable towards a target value
// @param out Reference to variable which will be modified
// @param target The value to move the variable towards
// @param step The amount that the variable will be moved by
// @return Whether or not the variable has reached the target
bool moveFloatTo(f32& out, f32 target, f32 step);
