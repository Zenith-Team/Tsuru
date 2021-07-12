#ifndef EFT_RESOURCE_H_
#define EFT_RESOURCE_H_

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

class Resource {
public:
    struct EmitterSet {  // Actual name not known 
        EmitterSetData* data;
        EmitterTblData* emitterRef;
        u32 numEmitter;
        u32 userData;

        // No idea why these are repeated
        EmitterSetData* _data;
        EmitterTblData* _emitterRef;
        u32 _numEmitter;
        u32 _userData;

        const char* name;
        u8 _unused;
        ParticleShader** shaders;
        u32 numShader;
        Primitive** primitives;
        u32 numPrimitive;
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
        u32 numPrimitive = emitterSets[emitterSetID].numPrimitive;
        Primitive** primitives = emitterSets[emitterSetID].primitives;

        for (u32 i = 0; i < numPrimitive; i++)
            if (primitives[i] != NULL && index == i)
                return primitives[i];

        return NULL;
    }

    System* system;
    u32 resourceID;
    Header* resource;
    char* strTbl;
    u8* textureDataTbl;
    EmitterSet* emitterSets;
    Heap* heap;
    ParticleShader** shaders;
    u32 numShader;
    Primitive** primitives;
    u32 numPrimitive;
};
static_assert(sizeof(Resource) == 0x30, "Resource size mismatch");

} } // namespace nw::eft

#endif // EFT_RESOURCE_H_
