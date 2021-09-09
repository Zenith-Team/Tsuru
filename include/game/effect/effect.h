#pragma once

#include <sead.h>
#include <types.h>
#include <nw/eft.h>
#include <game/effect/effectid.h>

class Effect {
public:
    Effect() {
        effectHandle.emitterSet = NULL;
        this->init();
    }

    void init();
    void init(EffectIDType effectID, const Mtx34* mtx, bool mtxHasScale);
    void init(EffectIDType effectID, const Vec3f* position, const Vec3u* rotation, const Vec3f* scale);

    bool update(const Vec3f* position, const Vec3u* rotation, const Vec3f* scale);
    bool update(const Mtx34* mtx, bool mtxHasScale);

    static bool spawn(EffectIDType effectID, const Mtx34* mtx, bool mtxHasScale);
    static bool spawn(EffectIDType effectID, const Vec3f* position, const Vec3u* rotation = nullptr, const Vec3f* scale = nullptr);

    Mtx34 mtx;                    // 0
    bool mtxHasScale;             // 30
    nw::eft::Handle effectHandle; // 34
    void* shaderParam;            // 3C
};


class EffectWrapper : public sead::IDisposer, public Effect, public sead::TListNode<EffectWrapper*> {
public:
    EffectWrapper();

    virtual ~EffectWrapper() {
        this->destroy();
    }

    SEAD_RTTI_BASE(EffectWrapper)

public:
    void init(EffectIDType effectID, const Mtx34* mtx, bool mtxHasScale);
    void init(EffectIDType effectID, const Vec3f* position, const Vec3u* rotation, const Vec3f* scale);

    bool update(const Vec3f* position, const Vec3u* rotation, const Vec3f* scale);
    bool update(const Mtx34* mtx, bool mtxHasScale);

    void destroy();

    EffectIDType effectID; // 60
    bool isActive;         // 64
};

class ActorEffect : public EffectWrapper {
    SEAD_RTTI_OVERRIDE(ActorEffect, EffectWrapper)

public:
    ActorEffect()
        : EffectWrapper()
    { }

    virtual ~ActorEffect() { }
};
