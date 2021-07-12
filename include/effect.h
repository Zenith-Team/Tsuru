#pragma once

#include "nw/eft.h"
#include "util/vec3.h"
#include "util/vec3u.h"
#include "util/mtx34.h"
#include "effects.h"
#include "sead.h"


class Effect {
public:
    Effect() {
        effectHadle.emitterSet = NULL;
        init();
    }

    void init();
    void init(Effects effectId, const Mtx34* mtx, bool mtxHasScale);
    void init(Effects effectId, const Vec3* position, const Vec3u* rotation, const Vec3* scale);

    bool update(const Vec3* position, const Vec3u* rotation, const Vec3* scale);
    bool update(const Mtx34* mtx, bool mtxHasScale);

    static bool spawn(Effects effectId, const Mtx34* mtx, bool mtxHasScale);
    static bool spawn(Effects effectId, const Vec3* position, const Vec3u* rotation, const Vec3* scale);

    Mtx34 mtx;                    // 0
    bool mtxHasScale;             // 30
    nw::eft::Handle effectHadle;  // 34
    void* shaderParam;            // 3C
};


class EffectWrapper : public sead::IDisposer, public Effect, public sead::TListNode<EffectWrapper*> {
public:
    EffectWrapper();

    virtual ~EffectWrapper() {
        destroy();
    }

    SEAD_RTTI_BASE(EffectWrapper)

public:
    void init(Effects effectId, const Mtx34* mtx, bool mtxHasScale);
    void init(Effects effectId, const Vec3* position, const Vec3u* rotation, const Vec3* scale);

    bool update(const Vec3* position, const Vec3u* rotation, const Vec3* scale);
    bool update(const Mtx34* mtx, bool mtxHasScale);

    void destroy();

    Effects effectId;  // 60
    bool isActive;     // 64
};

class ActorEffect : public EffectWrapper {
    SEAD_RTTI_OVERRIDE(ActorEffect, EffectWrapper)

public:
    ActorEffect()
        : EffectWrapper()
    { }

    virtual ~ActorEffect() { }
};
