#pragma once

#include "log.h"
#include "types.h"
#include "math/constants.h"
#include "math/functions.h"

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

    // Sets the parameters used for the easing operation, can be called multiple times for multi-use cases
    void init(f32 min, f32 max, f32 stepPercent) {
        this->min = min;
        this->max = max;
        this->step = valueFromPercent(stepPercent, min, max) - min;
    }

    // Eases the value towards the target value
    // @param value Reference to the current value to be eased
    // @return True if the value has reached the target value, false otherwise
    bool ease(f32& value) {
        this->iteration++;
        f32 next = this->func(percentFromValue(this->min * this->iteration + this->step, this->min, this->max) / 100) * (this->max - this->min) + this->min;

        if (next < this->max) {
            value = next;
            return false;
        };

        value = this->max;
        return true;
    }

    // https://easings.net

    static f32 sineIn(f32 x)     { return 1.0f - cosf((x * M_PI) / 2.0f); }
    static f32 sineOut(f32 x)    { return sinf((x * M_PI) / 2.0f); }
    static f32 sineInOut(f32 x)  { return -(cosf(M_PI * x) - 1.0f) / 2.0f; }

    static f32 quadIn(f32 x)     { return x * x; }
    static f32 quadOut(f32 x)    { return 1.0f - (1.0f - x) * (1.0f - x); }
    static f32 quadInOut(f32 x)  { return x < 0.5 ? 2 * x * x : 1 - powf(-2 * x + 2, 2) / 2; }

    static f32 cubicIn(f32 x)    { return x * x * x; }
    static f32 cubicOut(f32 x)   { return 1.0f - powf(1.0f - x, 3.0f); }
    static f32 cubicInOut(f32 x) { return x < 0.5f ? 4.0f * x * x * x : 1.0f - powf(-2.0f * x + 2.0f, 3.0f) / 2.0f; }

    static f32 quartIn(f32 x)    { return x * x * x * x; }
    static f32 quartOut(f32 x)   { return 1.0f - powf(1.0f - x, 4.0f); }
    static f32 quartInOut(f32 x) { return x < 0.5f ? 8.0f * x * x * x * x : 1.0f - powf(-2.0f * x + 2.0f, 4.0f) / 2.0f; }

    static f32 quintIn(f32 x)    { return x * x * x * x * x; }
    static f32 quintOut(f32 x)   { return 1.0f - powf(1.0f - x, 5.0f); }
    static f32 quintInOut(f32 x) { return x < 0.5f ? 16.0f * x * x * x * x * x : 1.0f - powf(-2.0f * x + 2.0f, 5.0f) / 2.0f; }

    static f32 expoIn(f32 x)     { return x == 0.0f ? 0.0f : powf(2.0f, 10.0f * x - 10.0f); }
    static f32 expoOut(f32 x)    { return x == 1.0f ? 1.0f : 1.0f - powf(2.0f, -10.0f * x); }
    static f32 expoInOut(f32 x)  { return x == 0.0f ? 0.0f : x == 1.0f ? 1.0f : x < 0.5f ? powf(2.0f, 20.0f * x - 10.0f) / 2.0f : (2.0f - powf(2.0f, -20.0f * x + 10.0f)) / 2.0f; }

    static f32 circIn(f32 x)     { return 1.0f - sqrtf(1.0f - powf(x, 2.0f)); }
    static f32 circOut(f32 x)    { return sqrtf(1.0f - powf(x - 1.0f, 2.0f)); }
    static f32 circInOut(f32 x)  { return x < 0.5f ? (1.0f - sqrtf(1.0f - powf(2.0f * x, 2.0f))) / 2.0f : (sqrtf(1.0f - powf(-2.0f * x + 2.0f, 2.0f)) + 1.0f) / 2.0f; }

private:
    f32 min;
    f32 max;
    f32 step;
    u32 iteration;
    EasingFunction func;
};
