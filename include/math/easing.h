#pragma once
#warning The "easing.h" header requires the currently unmapped symbol "__gh_float_scanf" to use.

#include <log.h>
#include <types.h>
#include <math/constants.h>
#include <math/functions.h>

// Main class for all easing operations
// @param func A reference to the easing function to be used
// @param min The start value
// @param max The end value
// @param stepPercent How big each easing step should be, in progress percentage (0-100). Put simply, the easing speed
class Easing {
    typedef f32 (*EasingFunction)(f32);

public:
    Easing(EasingFunction func, f32 min = 0.0f, f32 max = 0.0f, f32 stepPercent = 0.0f) {
        this->func = func;
        this->min = min;
        this->max = max;
        this->step = valueFromPercent(stepPercent, min, max) - min;
        this->iteration = 0;
    }

    // Thank you https://easings.net very cool

    static f32 SineIn(f32 x)     { return 1.0f - cosf((x * M_PI) / 2.0f); }
    static f32 SineOut(f32 x)    { return sinf((x * M_PI) / 2.0f); }
    static f32 SineInOut(f32 x)  { return -(cosf(M_PI * x) - 1.0f) / 2.0f; }
    
    static f32 QuadIn(f32 x)     { return x * x; }
    static f32 QuadOut(f32 x)    { return 1.0f - (1.0f - x) * (1.0f - x); }
    static f32 QuadInOut(f32 x)  { return x < 0.5 ? 2 * x * x : 1 - powf(-2 * x + 2, 2) / 2; }
    
    static f32 CubicIn(f32 x)    { return x * x * x; }
    static f32 CubicOut(f32 x)   { return 1.0f - powf(1.0f - x, 3.0f); }
    static f32 CubicInOut(f32 x) { return x < 0.5f ? 4.0f * x * x * x : 1.0f - powf(-2.0f * x + 2.0f, 3.0f) / 2.0f; }
    
    static f32 QuartIn(f32 x)    { return x * x * x * x; }
    static f32 QuartOut(f32 x)   { return 1.0f - powf(1.0f - x, 4.0f); }
    static f32 QuartInOut(f32 x) { return x < 0.5f ? 8.0f * x * x * x * x : 1.0f - powf(-2.0f * x + 2.0f, 4.0f) / 2.0f; }
    
    static f32 QuintIn(f32 x)    { return x * x * x * x * x; }
    static f32 QuintOut(f32 x)   { return 1.0f - powf(1.0f - x, 5.0f); }
    static f32 QuintInOut(f32 x) { return x < 0.5f ? 16.0f * x * x * x * x * x : 1.0f - powf(-2.0f * x + 2.0f, 5.0f) / 2.0f; }
    
    static f32 ExpoIn(f32 x)     { return x == 0.0f ? 0.0f : powf(2.0f, 10.0f * x - 10.0f); }
    static f32 ExpoOut(f32 x)    { return x == 1.0f ? 1.0f : 1.0f - powf(2.0f, -10.0f * x); }
    static f32 ExpoInOut(f32 x)  { return x == 0.0f ? 0.0f : x == 1.0f ? 1.0f : x < 0.5f ? powf(2.0f, 20.0f * x - 10.0f) / 2.0f : (2.0f - powf(2.0f, -20.0f * x + 10.0f)) / 2.0f; }
    
    static f32 CircIn(f32 x)     { return 1.0f - sqrtf(1.0f - powf(x, 2.0f)); }
    static f32 CircOut(f32 x)    { return sqrtf(1.0f - powf(x - 1.0f, 2.0f)); }
    static f32 CircInOut(f32 x)  { return x < 0.5f ? (1.0f - sqrtf(1.0f - powf(2.0f * x, 2.0f))) / 2.0f : (sqrtf(1.0f - powf(-2.0f * x + 2.0f, 2.0f)) + 1.0f) / 2.0f; }

    void init(f32 min, f32 max, f32 stepPercent) {
        this->min = min;
        this->max = max;
        this->step = valueFromPercent(stepPercent, min, max) - min;
    }

    bool ease(f32& value) {
        this->iteration++;
        f32 next = this->func(percentFromValue(this->min * this->iteration + this->step, this->min, this->max) / 100) * (this->max - this->min) + this->min;

        //LOG("%i: %f -> %f", this->iteration, value, next);

        if (next < this->max) {
            value = next;
            return false;
        };

        value = this->max;
        return true;
    }

private:
    f32 min;
    f32 max;
    f32 step;
    u32 iteration;
    EasingFunction func;
};