#include "tsuru/graphics/vbo.h"
#include "dynlibs/gx2/functions.h"

static u32 VarTypeToStreamCount(VBO::VarType type) {
    switch (type) {
        case VBO::VarType_BOOL:
        case VBO::VarType_INT:
        case VBO::VarType_UINT:
        case VBO::VarType_FLOAT:
        case VBO::VarType_VEC2:
        case VBO::VarType_VEC3:
        case VBO::VarType_VEC4:
        case VBO::VarType_BVEC2:
        case VBO::VarType_BVEC3:
        case VBO::VarType_BVEC4:
        case VBO::VarType_IVEC2:
        case VBO::VarType_UVEC2:
        case VBO::VarType_IVEC3:
        case VBO::VarType_UVEC3:
        case VBO::VarType_IVEC4:
        case VBO::VarType_UVEC4:
            return 1;
        case VBO::VarType_MAT2:
        case VBO::VarType_MAT2X3:
        case VBO::VarType_MAT2X4:
            return 2;
        case VBO::VarType_MAT3X2:
        case VBO::VarType_MAT3:
        case VBO::VarType_MAT3X4:
            return 3;
        case VBO::VarType_MAT4X2:
        case VBO::VarType_MAT4X3:
        case VBO::VarType_MAT4:
            return 4;
        default:
            return 0;
    }
}

static VBO::AttribFormat VarTypeToAttribFormat(VBO::VarType type, bool normalized) {
    switch (type) {
        case VBO::VarType_FLOAT:
            return VBO::AttribFormat_32_FLOAT;
        case VBO::VarType_VEC2:
        case VBO::VarType_MAT2:
        case VBO::VarType_MAT3X2:
        case VBO::VarType_MAT4X2:
            return VBO::AttribFormat_32_32_FLOAT;
        case VBO::VarType_VEC3:
        case VBO::VarType_MAT2X3:
        case VBO::VarType_MAT3:
        case VBO::VarType_MAT4X3:
            return VBO::AttribFormat_32_32_32_FLOAT;
        case VBO::VarType_VEC4:
        case VBO::VarType_MAT2X4:
        case VBO::VarType_MAT3X4:
        case VBO::VarType_MAT4:
            return VBO::AttribFormat_32_32_32_32_FLOAT;
    }

    if (normalized) {
        switch (type) {
            case VBO::VarType_BOOL:
                return VBO::AttribFormat_8_UNORM;
            case VBO::VarType_INT:
            case VBO::VarType_UINT:
                return VBO::AttribFormat_INVALID; // Not supported
            case VBO::VarType_BVEC2:
                return VBO::AttribFormat_8_8_UNORM;
            case VBO::VarType_BVEC3:
                return VBO::AttribFormat_INVALID; // Not supported
            case VBO::VarType_BVEC4:
                return VBO::AttribFormat_8_8_8_8_UNORM;
            case VBO::VarType_IVEC2:
            case VBO::VarType_UVEC2:
            case VBO::VarType_IVEC3:
            case VBO::VarType_UVEC3:
            case VBO::VarType_IVEC4:
            case VBO::VarType_UVEC4:
                return VBO::AttribFormat_INVALID; // Not supported
        }
    } else {
        switch (type) {
        case VBO::VarType_BOOL:
            return VBO::AttribFormat_8_UINT;
        case VBO::VarType_INT:
            return VBO::AttribFormat_32_SINT;
        case VBO::VarType_UINT:
            return VBO::AttribFormat_32_UINT;
        case VBO::VarType_BVEC2:
            return VBO::AttribFormat_8_8_UINT;
        case VBO::VarType_BVEC3:
            return VBO::AttribFormat_INVALID; // Not supported
        case VBO::VarType_BVEC4:
            return VBO::AttribFormat_8_8_8_8_UINT;
        case VBO::VarType_IVEC2:
            return VBO::AttribFormat_32_32_SINT;
        case VBO::VarType_UVEC2:
            return VBO::AttribFormat_32_32_UINT;
        case VBO::VarType_IVEC3:
            return VBO::AttribFormat_32_32_32_SINT;
        case VBO::VarType_UVEC3:
            return VBO::AttribFormat_32_32_32_UINT;
        case VBO::VarType_IVEC4:
            return VBO::AttribFormat_32_32_32_32_SINT;
        case VBO::VarType_UVEC4:
            return VBO::AttribFormat_32_32_32_32_UINT;
        }
    }

    return VBO::AttribFormat_INVALID;
}

static u32 AttribFormatByteSize(VBO::AttribFormat format) {
    switch (format) {
        case VBO::AttribFormat_8_UNORM:
        case VBO::AttribFormat_8_UINT:
            return 1;
        case VBO::AttribFormat_8_8_UNORM:
        case VBO::AttribFormat_8_8_UINT:
            return 2;
        case VBO::AttribFormat_32_UINT:
        case VBO::AttribFormat_32_SINT:
        case VBO::AttribFormat_32_FLOAT:
        case VBO::AttribFormat_8_8_8_8_UNORM:
        case VBO::AttribFormat_8_8_8_8_UINT:
            return 4;
        case VBO::AttribFormat_32_32_UINT:
        case VBO::AttribFormat_32_32_SINT:
        case VBO::AttribFormat_32_32_FLOAT:
            return 8;
        case VBO::AttribFormat_32_32_32_UINT:
        case VBO::AttribFormat_32_32_32_SINT:
        case VBO::AttribFormat_32_32_32_FLOAT:
            return 12;
        case VBO::AttribFormat_32_32_32_32_UINT:
        case VBO::AttribFormat_32_32_32_32_SINT:
        case VBO::AttribFormat_32_32_32_32_FLOAT:
            return 16;
        default:
            return 0;
    }
}

static u32 AttribFormatMask(VBO::AttribFormat format) {
    return attributeDestCompSelector[format & 0x1F];
}

VBO::VBO(u32 bufferIndex)
    : bufferIndex(bufferIndex)
    , bufferSize(0)
    , streamUsedCount(0)
    , built(false)
    , fetchShaderBufferSize(0)
    , fetchShaderBuffer(nullptr)
{ }

VBO::~VBO() {
    if (this->built && this->fetchShaderBuffer) {
        delete[] this->fetchShaderBuffer;
        this->fetchShaderBuffer = nullptr;
    }
}

bool VBO::setVertexAttrib(u32 index, u32 offset, VarType type, u32 arrayCount, bool normalized, u32 divisor) {
    if (this->built)
        return false;

    if (arrayCount == 0)
        arrayCount = 1;

    const u32 elemStreamCount = VarTypeToStreamCount(type);
    if (elemStreamCount == 0)
        return false;

    if (this->streamUsedCount + arrayCount * elemStreamCount > MAX_STREAM_COUNT)
        return false;

    const AttribFormat attribFormat = VarTypeToAttribFormat(type, normalized);
    if (attribFormat == VBO::AttribFormat_INVALID)
        return false;

    const u32 streamByteSize = AttribFormatByteSize(attribFormat);
    const u32 attribFormatMask = AttribFormatMask(attribFormat);

    const u32 indexType = (divisor == 0) ? GX2_ATTRIB_INDEX_PER_VERTEX
                                         : GX2_ATTRIB_INDEX_PER_INSTANCE;

    GX2AttribStream* streams = &this->streams[this->streamUsedCount];

    for (u32 i = 0; i < arrayCount; i++) {
        for (u32 j = 0; j < elemStreamCount; j++) {
            GX2AttribStream& stream = *streams++; // streams[i * arrayCount + j]
            stream.location = index++;            // index + i * arrayCount + j
            stream.buffer = this->bufferIndex;
            stream.offset = offset; offset += streamByteSize; // offset + (i * arrayCount + j) * streamByteSize
            stream.format = attribFormat;
            stream.destinationSelector = attribFormatMask;
            stream.endianSwap = GX2_ENDIANSWAP_DEFAULT;
            stream.indexType = indexType;
            stream.divisor = divisor;
        }
    }

    this->streamUsedCount += arrayCount * elemStreamCount;

    return true;
}

void VBO::build(sead::Heap* heap) {
    if (this->built)
        return;

    this->fetchShaderBufferSize = GX2CalcFetchShaderSizeEx(
        this->streamUsedCount,
        GX2_FETCH_SHADER_TESSELATION_NONE, // No Tessellation
        GX2_TESSELLATION_MODE_DISCRETE     // ^^^^^^^^^^^^^^^
    );

    this->fetchShaderBuffer = new (heap, GX2_SHADER_ALIGNMENT) u8[this->fetchShaderBufferSize];

    GX2InitFetchShaderEx(
        &this->fetchShader,
        this->fetchShaderBuffer,
        this->streamUsedCount,
        this->streams,
        GX2_FETCH_SHADER_TESSELATION_NONE, // No Tessellation
        GX2_TESSELLATION_MODE_DISCRETE     // ^^^^^^^^^^^^^^^
    );

    GX2Invalidate(GX2_INVALIDATE_CPU_SHADER, this->fetchShader.shaderProgram, this->fetchShader.shaderSize);

    this->built = true;
}

void VBO::bindBufferData(const void* bufferData, u32 size, u32 stride) {
    this->bufferData = bufferData;
    this->bufferSize = size;
    this->stride = stride;

    if (bufferData && size)
        GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, (void*)bufferData, size);
}

void VBO::bind() const {
    if (!this->built || !this->bufferData)
        return;

    GX2SetAttribBuffer(this->bufferIndex, this->bufferSize, this->stride, this->bufferData);
    GX2SetFetchShader(&this->fetchShader);
}
