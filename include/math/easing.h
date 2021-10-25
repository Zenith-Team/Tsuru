#pragma once

#include <types.h>
#include <math/constants.h>
#include <math/functions.h>

// https://easings.net

f32 sineIn(f32 x)     { return 1.0f - cosf((x * M_PI) / 2.0f); }
f32 sineOut(f32 x)    { return sinf((x * M_PI) / 2.0f); }
f32 sineInOut(f32 x)  { return -(cosf(M_PI * x) - 1.0f) / 2.0f; }

f32 quadIn(f32 x)     { return x * x; }
f32 quadOut(f32 x)    { return 1.0f - (1.0f - x) * (1.0f - x); }
f32 quadInOut(f32 x)  { return x < 0.5 ? 2 * x * x : 1 - powf(-2 * x + 2, 2) / 2; }

f32 cubicIn(f32 x)    { return x * x * x; }
f32 cubicOut(f32 x)   { return 1.0f - powf(1.0f - x, 3.0f); }
f32 cubicInOut(f32 x) { return x < 0.5f ? 4.0f * x * x * x : 1.0f - powf(-2.0f * x + 2.0f, 3.0f) / 2.0f; }

f32 quartIn(f32 x)    { return x * x * x * x; }
f32 quartOut(f32 x)   { return 1.0f - powf(1.0f - x, 4.0f); }
f32 quartInOut(f32 x) { return x < 0.5f ? 8.0f * x * x * x * x : 1.0f - powf(-2.0f * x + 2.0f, 4.0f) / 2.0f; }

f32 quintIn(f32 x)    { return x * x * x * x * x; }
f32 quintOut(f32 x)   { return 1.0f - powf(1.0f - x, 5.0f); }
f32 quintInOut(f32 x) { return x < 0.5f ? 16.0f * x * x * x * x * x : 1.0f - powf(-2.0f * x + 2.0f, 5.0f) / 2.0f; }

f32 expoIn(f32 x)     { return x == 0.0f ? 0.0f : powf(2.0f, 10.0f * x - 10.0f); }
f32 expoOut(f32 x)    { return x == 1.0f ? 1.0f : 1.0f - powf(2.0f, -10.0f * x); }
f32 expoInOut(f32 x)  { return x == 0.0f ? 0.0f : x == 1.0f ? 1.0f : x < 0.5f ? powf(2.0f, 20.0f * x - 10.0f) / 2.0f : (2.0f - powf(2.0f, -20.0f * x + 10.0f)) / 2.0f; }

f32 circIn(f32 x)     { return 1.0f - sqrtf(1.0f - powf(x, 2.0f)); }
f32 circOut(f32 x)    { return sqrtf(1.0f - powf(x - 1.0f, 2.0f)); }
f32 circInOut(f32 x)  { return x < 0.5f ? (1.0f - sqrtf(1.0f - powf(2.0f * x, 2.0f))) / 2.0f : (sqrtf(1.0f - powf(-2.0f * x + 2.0f, 2.0f)) + 1.0f) / 2.0f; }
