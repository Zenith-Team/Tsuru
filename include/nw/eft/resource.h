#pragma once

#include "types.h"

namespace nw { namespace eft {

struct EmitterTblData;
struct EmitterSetData;
struct FragmentShaderKey;
struct Header;
class Heap;
class ParticleShader;
class Primitive;
class System;
struct TextureRes;
struct VertexShaderKey;

class Resource { // Size: 0x30
public:
    struct EmitterSet { // Size: 0x38
        EmitterSetData* mData;
        EmitterTblData* mEmitterRef;
        u32 mNumEmitter;
        u32 mUserData;
        EmitterSetData* mData2;
        EmitterTblData* mEmitterRef2;
        u32 mNumEmitter2;
        u32 mUserData2;
        const char* mName;
        u8 mUnused;
        ParticleShader** mShaders;
        u32 mNumShader;
        Primitive** mPrimitives;
        u32 mNumPrimitive;
    };

    static_assert(sizeof(EmitterSet) == 0x38, "EmitterSet size mismatch");

public:
    Resource(Heap* heap, void* resource, u32 resourceID, System* system);
    virtual ~Resource(); // deleted

    void CreateFtexbTextureHandle(Heap* heap, void* data, TextureRes& texture);
    void CreateOriginalTextureHandle(Heap* heap, void* data, TextureRes& texture);
    void Initialize(Heap* heap, void* resource, u32 resourceID, System* system);
    static void DeleteTextureHandle(Heap* heap, TextureRes& texture, bool originalTexture);
    void Finalize(Heap* heap);
    ParticleShader* GetShader(s32 emitterSetID, const VertexShaderKey* vertexShaderKey, const FragmentShaderKey* fragmentShaderKey);

    Primitive* GetPrimitive(s32 emitterSetID, u32 index) {
        u32 numPrimitive = this->mEmitterSets[emitterSetID].mNumPrimitive;
        Primitive** primitives = this->mEmitterSets[emitterSetID].mPrimitives;

        for (u32 i = 0; i < numPrimitive; i++)
            if (primitives[i] != NULL && index == i)
                return primitives[i];
        
        return NULL;
    }

    System* mSystem;
    u32 mResourceID;
    Header* mResource;
    char* mStrTbl;
    u8* mTextureDataTbl;
    EmitterSet* mEmitterSets;
    Heap* mHeap;
    ParticleShader** mShaders;
    u32 mNumShader;
    Primitive** mPrimitives;
    u32 mNumPrimitive;
};

static_assert(sizeof(Resource) == 0x30, "Resource size mismatch");

} }
