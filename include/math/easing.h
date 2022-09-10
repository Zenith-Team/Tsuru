#pragma once

#include "log.h"
#include "types.h"
#include "math/constants.h"
#include "math/functions.h"

// Main class for all easing operations
// @param func A reference to the easing function to be used
// @param start The start value of the easing
// @param target The target value of the easing
// @param stepPercent How big each easing step should be, in progress percentage from 0.0 to 1.0. Put simply, the easing speed, and inversely, the smoothness
class Easing {
public:
    typedef f32 (*EasingFunction)(f32);

public:
    ENUM_CLASS(Type,
        Linear,
        SineIn,
        SineOut,
        SineInOut,
        QuadIn,
        QuadOut,
        QuadInOut,
        CubicIn,
        CubicOut,
        CubicInOut,
        QuartIn,
        QuartOut,
        QuartInOut,
        QuintIn,
        QuintOut,
        QuintInOut,
        ExpoIn,
        ExpoOut,
        ExpoInOut,
        CircIn,
        CircOut,
        CircInOut,
        BackIn,
        BackOut,
        BackInOut,
        ElasticIn,
        ElasticOut,
        ElasticInOut,
        BounceIn,
        BounceOut,
        BounceInOut
    );

public:
    Easing()
        : inited(false)
        , start(0.0f)
        , target(0.0f)
        , step(0.0f)
        , iteration(0.0f)
        , totalIterations(0.0f)
        , func(nullptr)
    { }

    Easing(EasingFunction func, f32 start, f32 target, f32 stepPercent) {
        this->set(func, start, target, stepPercent);
    }

    // Sets the parameters used for the easing operation and resets the current easing state, can be called multiple times for multi-use cases
    // Refer to the Easing class constructor for information on the arguments
    void set(EasingFunction func, f32 start, f32 target, f32 stepPercent) {
        this->inited = true;
        this->func = func;
        this->start = start;
        this->target = target;
        this->step = abs(valueFromPercent(stepPercent, start, target) - start);
        this->iteration = 0;
        this->totalIterations = abs(target - start) / this->step;
    }

    // Eases the value towards the target value
    // @param value Reference to the variable to be eased
    // @return True if the value has reached the target value, false if not. Returns true if the easing values were not initialized to prevent infinite loops
    bool ease(f32& value) {
        if (!this->inited) {
            LOG("%sWARNING > An Easing class instance was used with uninitialized values!", LogColor::Yellow);
            return true;
        }

        this->iteration++;
        f32 progress = abs(percentFromValue(this->start + this->step * this->iteration, this->start, this->target));
        f32 next = this->start + this->func(progress) * (this->target - this->start);
        //LOG("Easing (%i): %f -> %f [Change: %f | %f%]\n", this->iteration, value, next, next - value, progress * 100);

        if (this->iteration < totalIterations) {
            value = next;
            return false;
        };

        value = this->target;
        return true;
    }

    // https://easings.net

    static f32 linear(f32 x)       { return x + 1; }

    static f32 sineIn(f32 x)       { return 1.0f - cosf((x * M_PI) / 2.0f); }
    static f32 sineOut(f32 x)      { return sinf((x * M_PI) / 2.0f); }
    static f32 sineInOut(f32 x)    { return -(cosf(M_PI * x) - 1.0f) / 2.0f; }

    static f32 quadIn(f32 x)       { return x * x; }
    static f32 quadOut(f32 x)      { return 1.0f - (1.0f - x) * (1.0f - x); }
    static f32 quadInOut(f32 x)    { return x < 0.5 ? 2 * x * x : 1 - powf(-2 * x + 2, 2) / 2; }

    static f32 cubicIn(f32 x)      { return x * x * x; }
    static f32 cubicOut(f32 x)     { return 1.0f - powf(1.0f - x, 3.0f); }
    static f32 cubicInOut(f32 x)   { return x < 0.5f ? 4.0f * x * x * x : 1.0f - powf(-2.0f * x + 2.0f, 3.0f) / 2.0f; }

    static f32 quartIn(f32 x)      { return x * x * x * x; }
    static f32 quartOut(f32 x)     { return 1.0f - powf(1.0f - x, 4.0f); }
    static f32 quartInOut(f32 x)   { return x < 0.5f ? 8.0f * x * x * x * x : 1.0f - powf(-2.0f * x + 2.0f, 4.0f) / 2.0f; }

    static f32 quintIn(f32 x)      { return x * x * x * x * x; }
    static f32 quintOut(f32 x)     { return 1.0f - powf(1.0f - x, 5.0f); }
    static f32 quintInOut(f32 x)   { return x < 0.5f ? 16.0f * x * x * x * x * x : 1.0f - powf(-2.0f * x + 2.0f, 5.0f) / 2.0f; }

    static f32 expoIn(f32 x)       { return x == 0.0f ? 0.0f : powf(2.0f, 10.0f * x - 10.0f); }
    static f32 expoOut(f32 x)      { return x == 1.0f ? 1.0f : 1.0f - powf(2.0f, -10.0f * x); }
    static f32 expoInOut(f32 x)    { return x == 0.0f ? 0.0f : x == 1.0f ? 1.0f : x < 0.5f ? powf(2.0f, 20.0f * x - 10.0f) / 2.0f : (2.0f - powf(2.0f, -20.0f * x + 10.0f)) / 2.0f; }

    static f32 circIn(f32 x)       { return 1.0f - sqrtf(1.0f - powf(x, 2.0f)); }
    static f32 circOut(f32 x)      { return sqrtf(1.0f - powf(x - 1.0f, 2.0f)); }
    static f32 circInOut(f32 x)    { return x < 0.5f ? (1.0f - sqrtf(1.0f - powf(2.0f * x, 2.0f))) / 2.0f : (sqrtf(1.0f - powf(-2.0f * x + 2.0f, 2.0f)) + 1.0f) / 2.0f; }

    static f32 backIn(f32 x)       { return 2.70158f * x * x * x - 1.70158f * x * x; }
    static f32 backOut(f32 x)      { return 1.0f + 2.70158f * powf(x - 1.0f, 3.0f) + 1.70158f * powf(x - 1.0f, 2.0f); }
    static f32 backInOut(f32 x)    { return x < 0.5f ? (powf(2.0f * x, 2.0f) * (3.5949095f * 2.0f * x - 2.5949095f)) / 2.0f : (powf(2.0f * x - 2.0f, 2.0f) * (3.5949095f * (x * 2.0f - 2.0f) + 2.5949095f) + 2.0f) / 2.0f; }

    static f32 elasticIn(f32 x)    { return x == 0.0f ? 0.0f : x == 1.0f ? 1.0f : -powf(2.0f, 10.0f * x - 10.0f) * sinf((x * 10.0f - 10.75f) * (2.0f * M_PI / 3.0f)); }
    static f32 elasticOut(f32 x)   { return x == 0.0f ? 0.0f : x == 1.0f ? 1.0f : powf(2.0f, -10.0f * x) * sinf((x * 10.0f - 0.75f) * (2.0f * M_PI / 3.0f)) + 1.0f; }
    static f32 elasticInOut(f32 x) { return x == 0.0f ? 0.0f : x == 1.0f ? 1.0f : x < 0.5f ? -(powf(2.0f, 20.0f * x - 10.0f) * sinf((20.0f * x - 11.125f) * (2.0f * M_PI / 4.5f))) / 2.0f : (powf(2.0f, -20.0f * x + 10.0f) * sinf((20.f * x - 11.125f) * (2.0f * M_PI / 4.5f))) / 2.0f + 1.0f; }

    static f32 bounceIn(f32 x)     { return 1.0f - bounceOut(1.0f - x); }
    static f32 bounceOut(f32 x)    { return x < 1.0f / 2.75f ? 7.5625f * x * x : x < 2.0f / 2.75f ? 7.5625f * (x - 1.5f / 2.75f) * (x - 1.5f / 2.75f) + 0.75f : x < 2.5f / 2.75f ? 7.5625f * (x - 2.25f / 2.75f) * (x - 2.25f / 2.75f) + 0.9375f : 7.5625f * (x - 2.625f / 2.75f) * (x - 2.625f / 2.75f) + 0.984375f; }
    static f32 bounceInOut(f32 x)  { return x < 0.5f ? (1.0f - bounceOut(1.0f - 2.0f * x)) / 2.0f : (1.0f + bounceOut(2.0f * x - 1.0f)) / 2.0f; }

    static EasingFunction TypeToEaseFunc(Type::__type__ type) {
        switch (type) {
            case Type::Linear: return &Easing::linear;

            case Type::SineIn: return &Easing::sineIn;
            case Type::SineOut: return &Easing::sineOut;
            case Type::SineInOut: return &Easing::sineInOut;

            case Type::QuadIn: return &Easing::quadIn;
            case Type::QuadOut: return &Easing::quadOut;
            case Type::QuadInOut: return &Easing::quadInOut;

            case Type::CubicIn: return &Easing::cubicIn;
            case Type::CubicOut: return &Easing::cubicOut;
            case Type::CubicInOut: return &Easing::cubicInOut;

            case Type::QuartIn: return &Easing::quartIn;
            case Type::QuartOut: return &Easing::quartOut;
            case Type::QuartInOut: return &Easing::quartInOut;

            case Type::QuintIn: return &Easing::quintIn;
            case Type::QuintOut: return &Easing::quintOut;
            case Type::QuintInOut: return &Easing::quintInOut;

            case Type::ExpoIn: return &Easing::expoIn;
            case Type::ExpoOut: return &Easing::expoOut;
            case Type::ExpoInOut: return &Easing::expoInOut;

            case Type::CircIn: return &Easing::circIn;
            case Type::CircOut: return &Easing::circOut;
            case Type::CircInOut: return &Easing::circInOut;

            case Type::BackIn: return &Easing::backIn;
            case Type::BackOut: return &Easing::backOut;
            case Type::BackInOut: return &Easing::backInOut;

            case Type::ElasticIn: return &Easing::elasticIn;
            case Type::ElasticOut: return &Easing::elasticOut;
            case Type::ElasticInOut: return &Easing::elasticInOut;

            case Type::BounceIn: return &Easing::bounceIn;
            case Type::BounceOut: return &Easing::bounceOut;
            case Type::BounceInOut: return &Easing::bounceInOut;

            default: return &Easing::linear;
        }
    }

private:
    bool inited;
    f32 start;
    f32 target;
    f32 step;
    u32 iteration;
    f32 totalIterations;
    EasingFunction func;
};
