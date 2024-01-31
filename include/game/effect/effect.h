#pragma once

#include "types.h"
#include "nw/effect.h"
#include "game/effect/effectid.h"
#include "heap/seadDisposer.h"
#include "container/seadTList.h"
#include "prim/seadRuntimeTypeInfo.h"
#include "math/seadMatrix.h"

class Effect {
public:
    Effect() {
        this->clear();
    }

    void clear();

    nw::eft::EmitterSet* getEmitterSet();

    void init(u32 effectID, const sead::Matrix34f* mtx, bool mtxHasScale);
    void init(u32 effectID, const sead::Vector3f* position, const sead::Vector3u* rotation, const sead::Vector3f* scale);

    bool update(const sead::Vector3f* position, const sead::Vector3u* rotation, const sead::Vector3f* scale);
    bool update(const sead::Matrix34f* mtx, bool mtxHasScale);

    // Spawns an effect at a position
    // @param effectID ID of the effect to spawn
    // @param mtx Matrix to spawn the effect at
    // @param mtxHasScale Whether or not the matrix has scale
    static bool spawn(u32 effectID, const sead::Matrix34f* mtx, bool mtxHasScale);
    // Spawns an effect at a position
    // @param effectID ID of the effect to spawn
    // @param position Position to spawn the effect at
    // @param rotation Optional pointer to a rotation for the effect
    // @param scale Optional pointer to a scale for the effect
    static bool spawn(u32 effectID, const sead::Vector3f* position, const sead::Vector3u* rotation = nullptr, const sead::Vector3f* scale = nullptr);

    sead::Matrix34f mtx;          // 0
    bool mtxHasScale;             // 30
    nw::eft::Handle effectHandle; // 34
    void* shaderParam;            // 3C
};

static_assert(sizeof(Effect) == 0x40, "Effect size mismatch");

class EffectWrapper : public sead::IDisposer, public Effect, public sead::TListNode<EffectWrapper*> {
public:
    EffectWrapper();
    ~EffectWrapper();

    SEAD_RTTI_BASE_DECL(EffectWrapper);

    bool update(const u32 effectID, const sead::Vector3f* position, const sead::Vector3u* rotation, const sead::Vector3f* scale);
    bool update(const u32 effectID, const sead::Matrix34f* mtx, bool mtxHasScale);

    void destroy();

    EffectID effectID;   // 60
    bool isActive;       // 64
};

static_assert(sizeof(EffectWrapper) == 0x68, "EffectWrapper size mismatch");
