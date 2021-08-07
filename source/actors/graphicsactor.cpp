#include <game/actor/stage/stageactor.h>
#include <sead.h>
#include <dynlibs/gx2/functions.h>
#include <dynlibs/os/functions.h>
#include <log.h>
#include <string.h>

//! Extremely scuffed temporary code (tried to implement functions needed from wut manually here(pain))

// Data structures
struct Header {
    u32 magic;
    u32 headerSize;
    u32 majorVersion;
    u32 minorVersion;
    u32 gpuVersion;
    u32 align;
    u32 unk1[2];
};
struct BlockHeader {
    u32 magic;
    u32 headerSize;
    u32 majorVersion;
    u32 minorVersion;
    u32 type;
    u32 dataSize;
    u32 id;
    u32 index;
};
struct RelocationHeader {
    u32 magic;
    u32 headerSize;
    u32 unk1;
    u32 dataSize;
    u32 dataOffset;
    u32 textSize;
    u32 textOffset;
    u32 patchBase;
    u32 patchCount;
    u32 patchOffset;
};
struct ShaderGroup {
    GX2FetchShader fetchShader;
    void* fetchShaderProgram;
    GX2PixelShader* pixelShader;
    GX2VertexShader* vertexShader;
    u32 numAttributes;
    GX2AttribStream attributes[16];
};

// Data functions
static bool GetHeaderVersions(u32* majorVersion, u32* minorVersion, u32* gpuVersion, const void* file) {
    Header* header = (Header*)file;
   *majorVersion = 0;
   *minorVersion = 0;
   *gpuVersion = 0;

    if (header->magic != 0x47667832) return false;

   *majorVersion = header->majorVersion;
   *minorVersion = header->minorVersion;
   *gpuVersion = header->gpuVersion;
    return true;
}
static bool CheckHeaderVersions(const void* file) {
    u32 majorVersion, minorVersion, gpuVersion;

    if (!GetHeaderVersions(&majorVersion, &minorVersion, &gpuVersion, file))
        return false;
    if (majorVersion != 7)
        return false;
    if (minorVersion != 1)
        return false;
    else
        return true;
}
static bool CheckBlockHeaderMagicVersions(const BlockHeader* header) {
    if (header->magic != 0x424C4B7B)
        return false;
    if (header->majorVersion != 1)
        return false;
    else
        return true;
}
static u32 GetBlockCount(u32 type, const void* file) {
    const u8* ptr = (const u8*)file;
    const Header* fileHeader = (const Header*)file;
    const BlockHeader* blockHeader;
    u32 count = 0;

    if (!file)
        return 0;
    if (!CheckHeaderVersions(file)) 
        return 0;
    
    ptr += fileHeader->headerSize;
    blockHeader = (const BlockHeader*)ptr;

    while (CheckBlockHeaderMagicVersions(blockHeader)) {
        if (blockHeader->type == type)
            count++;
        else if (blockHeader->type == 1)
            break;
        
        ptr += blockHeader->headerSize + blockHeader->dataSize;
        blockHeader = (const BlockHeader*)ptr;
    }

    return count;
}
static u32 GetBlockDataSize(u32 type, u32 index, const void* file) {
    const u8* ptr = (const u8*)file;
    const Header* fileHeader = (const Header*)file;
    const BlockHeader* blockHeader;
    u32 count = 0;

    if (!file)
        return 0;
    if (!CheckHeaderVersions(file))
        return 0;
    
    ptr += fileHeader->headerSize;
    blockHeader = (const BlockHeader*)ptr;

    while (CheckBlockHeaderMagicVersions(blockHeader)) {
        if (blockHeader->type == type) {
            if (count == index)
                return 0;
            
            count++;
        }

        else if (blockHeader->type == 1)
            break;

        ptr += blockHeader->headerSize + blockHeader->dataSize;
        blockHeader = (const BlockHeader*)ptr;
    }

    return 0;
}
static bool RelocateBlockEx(const RelocationHeader* relocationHeader, const u32* patchTable, u8* dst) {
    for (u32 i = 0; i < relocationHeader->patchCount; ++i) {
        u32* target;
        u32 offset = patchTable[i];

        if (offset == 0)
            continue;
        if (((offset & 0xFFF00000) == 0xD0600000) && (offset & 0xFFF00000) == 0xFFF00000)
            return false;
        
        target = (u32*)(dst + (offset & ~0xFFF00000));

        if (!((*target & 0xFFF00000) == 0xD0600000) && (*target & 0xFFF00000) == 0xFFF00000)
            return false;
        
        *target = (uintptr_t)(dst + (*target & ~0xFFF00000));
    }

    return true;
}
static bool RelocateBlock(const BlockHeader* blockHeader, void* dst) {
    const u8* blockData = ((const u8*)blockHeader) + blockHeader->headerSize;
    const RelocationHeader* relocationHeader;
    const u32* patchTable;

    if (!blockHeader || !dst)
        return false;
    
    relocationHeader = (const RelocationHeader*)(blockData + blockHeader->dataSize - sizeof(RelocationHeader));
    if (relocationHeader->magic != 0x7D424C4B)
        return false;
    if (!(relocationHeader->patchOffset & 0xFFF00000) == 0xFFF00000)
        return false;
    
    patchTable = (const u32*)(blockData + (relocationHeader->patchOffset & ~0xFFF00000));
    return RelocateBlockEx(relocationHeader, patchTable, (u8*)dst);
}
static bool GetGenericBlock(u32 blockTypeHeader, void* header, u32 blockTypeProgram1, void** outProgramPtr1, void* program1, u32 blockTypeProgram2, u32** outProgramPtr2, u32* program2, u32 index, const void* file) {
    const u8* ptr = (const u8*)file;
    const Header* fileHeader = (const Header*)file;
    const BlockHeader* blockHeader;
    u32 headerCount = 0;
    u32 program1Count = 0;
    u32 program2Count = 0;
    bool result = false;

    if (!header || !file)
        return false;
    
    ptr += fileHeader->headerSize;
    blockHeader = (const BlockHeader*)ptr;

    while (CheckBlockHeaderMagicVersions(blockHeader)) {
        ptr += blockHeader->headerSize;

        if (blockHeader->type == blockTypeHeader) {
            if (headerCount == index) {
                OSBlockMove(header, ptr, blockHeader->dataSize, 0);

                if (blockTypeHeader != 11)
                    if (!RelocateBlock(blockHeader, header))
                        return false;
            }

            headerCount++;
        }

        else if (blockHeader->type == blockTypeProgram1) {
            if (program1Count == index) {
                *outProgramPtr1 = program1;
                OSBlockMove(program1, ptr, blockHeader->dataSize, 0);
            }

            program1Count++;
        }

        else if (program2 && blockHeader->type == blockTypeProgram2) {
            if (program2Count == index) {
                *outProgramPtr2 = program2;
                OSBlockMove(program2, ptr, blockHeader->dataSize, 0);
            }

            program2Count++;
        }

        else if (blockHeader->type == 1)
            break;
        
        if (headerCount > index && program1Count > index) {
            if (!program2 || program2Count > index) {
                result = true;
                break;
            }
        }

        ptr += blockHeader->dataSize;
        blockHeader = (const BlockHeader*)ptr;
    }

    return result;
}

// Shortcuts
bool GetPixelShader(GX2PixelShader* shader, void* program, u32 index, const void* file) {
    if (!(((uintptr_t)program) & (0x100 - 1)) == 0)
        return false;
    else
        return GetGenericBlock(6, shader, 7, &shader->shader_data, program, 0, NULL, NULL, index, file);
}
#define GX2_SEL_MASK(x, y, z, w) (((x) << 24) | ((y) << 16) | ((z) << 8) | (w))
#define GX2_COMP_MAP(x, y, z, w) (((x) << 24) | ((y) << 16) | ((z) << 8) | (w))

// Location
static s32 GetVertexAttribVarLocation(const GX2VertexShader* shader, const char* name) {
    for (u32 i = 0; i < shader->attribute_vars_count; ++i) {
        if (strcmp(shader->attribute_var[i].name, name) == 0)
            return shader->attribute_var[i].location;
    }

    return -1;
}

// Attributes
static u32 GetAttribFormatSel(u32 format) {
    switch (format) {
        case GX2_ATTRIB_FORMAT_8_UNORM:
        case GX2_ATTRIB_FORMAT_8_UINT:
        case GX2_ATTRIB_FORMAT_8_SNORM:
        case GX2_ATTRIB_FORMAT_8_SINT:
        case GX2_ATTRIB_FORMAT_32_FLOAT:
        return GX2_SEL_MASK(0, 4, 4, 5);

        case GX2_ATTRIB_FORMAT_8_8_UNORM:
        case GX2_ATTRIB_FORMAT_8_8_UINT:
        case GX2_ATTRIB_FORMAT_8_8_SNORM:
        case GX2_ATTRIB_FORMAT_8_8_SINT:
        case GX2_ATTRIB_FORMAT_32_32_FLOAT:
        return GX2_SEL_MASK(0, 1, 4, 5);

        case GX2_ATTRIB_FORMAT_32_32_32_FLOAT:
        return GX2_SEL_MASK(0, 1, 2, 5);

        case GX2_ATTRIB_FORMAT_8_8_8_8_UNORM:
        case GX2_ATTRIB_FORMAT_8_8_8_8_UINT:
        case GX2_ATTRIB_FORMAT_8_8_8_8_SNORM:
        case GX2_ATTRIB_FORMAT_8_8_8_8_SINT:
        case GX2_ATTRIB_FORMAT_32_32_32_32_FLOAT:
        return GX2_SEL_MASK(0, 1, 2, 3);

        default:
        return GX2_SEL_MASK(4, 4, 4, 5);
    }
}

// Free shaders
bool FreePixelShader(GX2PixelShader* shader) {
    if (shader->shader_program_buffer.buffer)
        GX2RDestroyBufferEx(&shader->shader_program_buffer, 0);
    
    MEMFreeToDefaultHeap(shader);

    return true;
}
bool FreeVertexShader(GX2VertexShader* shader) {
    if (shader->shader_program_buffer.buffer)
        GX2RDestroyBufferEx(&shader->shader_program_buffer, 0);
    
    MEMFreeToDefaultHeap(shader);
    
    return true;
}
bool FreeShaderGroup(ShaderGroup* group) {
    if (group->fetchShaderProgram) {
        MEMFreeToDefaultHeap(group->fetchShaderProgram);
        group->fetchShaderProgram = NULL;
    }

    if (group->pixelShader) {
        FreePixelShader(group->pixelShader);
        group->pixelShader = NULL;
    }

    if (group->vertexShader) {
        FreeVertexShader(group->vertexShader);
        group->vertexShader = NULL;
    }

    return true;
}

// Load shaders
GX2VertexShader* LoadGFDVertexShader(u32 index, const void* file) {
    u32 headerSize, programSize;
    GX2VertexShader* shader = nullptr;
    void* program = nullptr;

    if (index >= GetBlockCount(3, file))
        goto error;
    
    headerSize = GetBlockDataSize(3, index, file);
    if (!headerSize)
        goto error;
    
    programSize = GetBlockDataSize(5, index, file);
    if (!programSize)
        goto error;

    shader = (GX2VertexShader*)MEMAllocFromDefaultHeapEx(headerSize, 64);
    if (!shader)
        goto error;

    shader->shader_program_buffer.flags = GX2R_RESOURCE_BIND_SHADER_PROGRAM | GX2R_RESOURCE_USAGE_CPU_READ | GX2R_RESOURCE_USAGE_CPU_WRITE | GX2R_RESOURCE_USAGE_GPU_READ;
    shader->shader_program_buffer.elemSize = programSize;
    shader->shader_program_buffer.elemCount = 1;
    shader->shader_program_buffer.buffer = NULL;

    if (!GX2RCreateBuffer(&shader->shader_program_buffer))
        goto error;
    
    program = GX2RLockBufferEx(&shader->shader_program_buffer, 0);
    if (!program)
        goto error;
    
    if (!GetGenericBlock(3, shader, 5, &shader->shader_data, program, 0, NULL, NULL, index, file)) {
        GX2RUnlockBufferEx(&shader->shader_program_buffer, GX2R_RESOURCE_DISABLE_CPU_INVALIDATE | GX2R_RESOURCE_DISABLE_GPU_INVALIDATE);
        goto error;
    }

    GX2RUnlockBufferEx(&shader->shader_program_buffer, 0);
    GX2Invalidate(72, shader->shader_data, shader->shader_size);

    return shader;

error:
    if (shader) {
        if (shader->shader_program_buffer.buffer)
            GX2RDestroyBufferEx(&shader->shader_program_buffer, 0);
        
        MEMFreeToDefaultHeap(shader);
    }

    return NULL;
}
GX2PixelShader* LoadGFDPixelShader(u32 index, const void* file) {
    u32 headerSize, programSize;
    GX2PixelShader* shader = nullptr;
    void* program = nullptr;

    if (index >= GetBlockCount(6, file))
        goto error;

    headerSize = GetBlockDataSize(6, index, file);
    if (!headerSize)
        goto error;
    
    programSize = GetBlockDataSize(7, index, file);
    if (!programSize)
        goto error;
    
    shader = (GX2PixelShader*)MEMAllocFromDefaultHeapEx(headerSize, 64);
    if (!shader)
        goto error;
    
    shader->shader_program_buffer.flags = GX2R_RESOURCE_BIND_SHADER_PROGRAM | GX2R_RESOURCE_USAGE_CPU_READ | GX2R_RESOURCE_USAGE_CPU_WRITE | GX2R_RESOURCE_USAGE_GPU_READ;
    shader->shader_program_buffer.elemSize = programSize;
    shader->shader_program_buffer.elemCount = 1;
    shader->shader_program_buffer.buffer = NULL;

    if (!GX2RCreateBuffer(&shader->shader_program_buffer))
        goto error;
    
    program = GX2RLockBufferEx(&shader->shader_program_buffer, 0);
    if (!program)
        goto error;
    
    if (!GetPixelShader(shader, program, index, file)) {
        GX2RUnlockBufferEx(&shader->shader_program_buffer, GX2R_RESOURCE_DISABLE_CPU_INVALIDATE | GX2R_RESOURCE_DISABLE_GPU_INVALIDATE);
        goto error;
    }

    GX2RUnlockBufferEx(&shader->shader_program_buffer, 0);
    GX2Invalidate(72, shader->shader_data, shader->shader_size);
    return shader;

error:
    if (shader) {
        if (shader->shader_program_buffer.buffer)
            GX2RDestroyBufferEx(&shader->shader_program_buffer, 0);
        
        MEMFreeToDefaultHeap(shader);
    }

    return NULL;
}
bool LoadGFDShaderGroup(ShaderGroup* group, u32 index, const void* file) {
    OSBlockSet(group, 0, sizeof(ShaderGroup));

    group->vertexShader = LoadGFDVertexShader(index, file);
    group->pixelShader = LoadGFDPixelShader(index, file);

    if (!group->vertexShader || !group->pixelShader) {
        FreeShaderGroup(group);
        return false;
    }

    return true;
}

// Init shaders
bool InitShaderAttribute(ShaderGroup* group, const char* name, u32 buffer, u32 offset, u32 format) {
    GX2AttribStream* attrib;
    s32 location;

    location = GetVertexAttribVarLocation(group->vertexShader, name);
    if (location == -1)
        return false;
    
    attrib = &group->attributes[group->numAttributes++];
    attrib->location = location;
    attrib->buffer = buffer;
    attrib->offset = offset;
    attrib->format = format;
    attrib->index_type = GX2_ATTRIB_INDEX_PER_VERTEX;
    attrib->divisor = 0;
    attrib->destination_selector = GetAttribFormatSel(format);
    attrib->endian_swap = GX2_ENDIANSWAP_DEFAULT;
    return true;
}
bool InitFetchShader(ShaderGroup* group) {
    u32 size = GX2CalcFetchShaderSizeEx(group->numAttributes, GX2_FETCH_SHADER_TESSELATION_NONE, 0);

    group->fetchShaderProgram = MEMAllocFromDefaultHeapEx(size, GX2_SHADER_ALIGNMENT);

    GX2InitFetchShaderEx(&group->fetchShader, group->fetchShaderProgram, group->numAttributes, group->attributes, GX2_FETCH_SHADER_TESSELATION_NONE, 0);

    GX2Invalidate(72, group->fetchShaderProgram, size);
    return true;
}

// Render data
static const f32 PositionData[] =  {
     1.0f, -1.0f, 0.0f, 1.0f,
     0.0f,  1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 1.0f, 1.0f
};

static const f32 ColorData[] = {
    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f
};

class GraphicsActor : public StageActor {
public:
    GraphicsActor(const ActorBuildInfo* buildInfo);
    ~GraphicsActor() { }

    static ActorBase* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onDraw() override;

    void render();

    bool mHasRendered;

    f32* colors;
};

const Profile GraphicsActorProfile(&GraphicsActor::build, ProfileID::GraphicsActor, "GraphicsActor", nullptr, 0);

GraphicsActor::GraphicsActor(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
    , mHasRendered(false)
{ }

ActorBase* GraphicsActor::build(const ActorBuildInfo* buildInfo) {
    return new GraphicsActor(buildInfo);
}

u32 GraphicsActor::onCreate() {
    render();

    return 1;
}

u32 GraphicsActor::onDraw() {
    render();

    return 1;
}

void GraphicsActor::render() {
    LOG("rendering");

    GX2RBuffer positionBuffer = { 0 };
    GX2RBuffer colorBuffer = { 0 };
    ShaderGroup group = { 0 };
    void* buffer = nullptr;
    static const u8* gshFileData;

    sead::FileDevice::LoadArg file;

    file.mPath = "superres/shader/pos_col_shader.gsh";

    gshFileData = sead::FileDeviceMgr::sInstance->tryLoad(file);

    if (!gshFileData)
        goto exit;

    if (!LoadGFDShaderGroup(&group, 0, gshFileData))
        goto exit;

    InitShaderAttribute(&group, "aPosition", 0, 0, GX2_ATTRIB_FORMAT_32_32_32_32_FLOAT);
    InitShaderAttribute(&group, "aColour", 1, 0, GX2_ATTRIB_FORMAT_32_32_32_32_FLOAT);
    InitFetchShader(&group);
    
    positionBuffer.flags = GX2R_RESOURCE_BIND_VERTEX_BUFFER | GX2R_RESOURCE_USAGE_CPU_READ | GX2R_RESOURCE_USAGE_CPU_WRITE | GX2R_RESOURCE_USAGE_GPU_READ;
    positionBuffer.elemSize = 4* 4;
    positionBuffer.elemCount = 3;
    GX2RCreateBuffer(&positionBuffer);
    buffer = GX2RLockBufferEx(&positionBuffer, 0);
    OSBlockMove(buffer, PositionData, positionBuffer.elemSize* positionBuffer.elemCount, 0);
    GX2RUnlockBufferEx(&positionBuffer, 0);

    colorBuffer.flags = GX2R_RESOURCE_BIND_VERTEX_BUFFER | GX2R_RESOURCE_USAGE_CPU_READ | GX2R_RESOURCE_USAGE_CPU_WRITE | GX2R_RESOURCE_USAGE_GPU_READ;
    colorBuffer.elemSize = 4* 4;
    colorBuffer.elemCount = 3;
    GX2RCreateBuffer(&colorBuffer);
    buffer = GX2RLockBufferEx(&colorBuffer, 0);
    OSBlockMove(buffer, ColorData, colorBuffer.elemSize* colorBuffer.elemCount, 0);
    GX2RUnlockBufferEx(&colorBuffer, 0);

    goto renderstep;

renderstep:
    mHasRendered = true;

    f32* colors = (f32*)GX2RLockBufferEx(&colorBuffer, 0);

    colors[0] = 1.0f;
    colors[1] = colors[1] >= 1.0f ? 0.0f : (colors[1] + 0.01f);
    colors[2] = colors[2] >= 1.0f ? 0.0f : (colors[2] + 0.01f);
    colors[3] = 1.0f;

    colors[4] = colors[4] >= 1.0f ? 0.0f : (colors[4] + 0.01f);
    colors[5] = 1.0f;
    colors[6] = colors[6] >= 1.0f ? 0.0f : (colors[6] + 0.01f);
    colors[7] = 1.0f;

    colors[8] = colors[8] >= 1.0f ? 0.0f : (colors[8] + 0.01f);
    colors[9] = colors[9] >= 1.0f ? 0.0f : (colors[9] + 0.01f);
    colors[10] = 1.0f;
    colors[11] = 1.0f;

    GX2RUnlockBufferEx(&colorBuffer, 0);

    GX2SetFetchShader(&group.fetchShader);
    GX2SetVertexShader(group.vertexShader);
    GX2SetPixelShader(group.pixelShader);
    GX2RSetAttributeBuffer(&positionBuffer, 0, positionBuffer.elemSize, 0);
    GX2RSetAttributeBuffer(&colorBuffer, 1, colorBuffer.elemSize, 0);
    GX2DrawEx(GX2_PRIMITIVE_TRIANGLES, 3, 0, 1);

    goto exit;

exit:
    GX2RDestroyBufferEx(&positionBuffer, 0);
    GX2RDestroyBufferEx(&colorBuffer, 0);

    delete gshFileData;

    return;
}
