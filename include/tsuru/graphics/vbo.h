#pragma once

#include "sead/heap.h"
#include "dynlibs/gx2/types.h"

class VBO {
public:
    enum VarType {
        VarType_BOOL = 1,
        VarType_INT,
        VarType_UINT,
        VarType_FLOAT,
        VarType_VEC2 = 9,
        VarType_VEC3,
        VarType_VEC4,
        VarType_BVEC2,
        VarType_BVEC3,
        VarType_BVEC4,
        VarType_IVEC2,
        VarType_IVEC3,
        VarType_IVEC4,
        VarType_UVEC2,
        VarType_UVEC3,
        VarType_UVEC4,
        VarType_MAT2,
        VarType_MAT2X3,
        VarType_MAT2X4,
        VarType_MAT3X2,
        VarType_MAT3,
        VarType_MAT3X4,
        VarType_MAT4X2,
        VarType_MAT4X3,
        VarType_MAT4
    };

    enum AttribFormat {
        AttribFormat_8_UNORM           = 0x000,
        AttribFormat_8_UINT            = 0x100,
        AttribFormat_8_8_UNORM         = 0x004,
        AttribFormat_8_8_UINT          = 0x104,
        AttribFormat_32_UINT           = 0x105,
        AttribFormat_32_SINT           = 0x305,
        AttribFormat_32_FLOAT          = 0x806,
        AttribFormat_32_32_UINT        = 0x10C,
        AttribFormat_32_32_SINT        = 0x30C,
        AttribFormat_32_32_FLOAT       = 0x80D,
        AttribFormat_8_8_8_8_UNORM     = 0x00A,
        AttribFormat_8_8_8_8_UINT      = 0x10A,
        AttribFormat_32_32_32_UINT     = 0x110,
        AttribFormat_32_32_32_SINT     = 0x310,
        AttribFormat_32_32_32_FLOAT    = 0x811,
        AttribFormat_32_32_32_32_UINT  = 0x112,
        AttribFormat_32_32_32_32_SINT  = 0x312,
        AttribFormat_32_32_32_32_FLOAT = 0x813,

        AttribFormat_INVALID = 0xFFFFFFFF
    };

private:
    enum {
        MAX_STREAM_COUNT = 32
    };

public:
    // @param bufferIdx: index of attribute buffer to use (0-15) Unlike GX2, only 1 buffer per drawcall (limitation of this abstraction)
    VBO(u32 bufferIdx);
    ~VBO();

    // Set definition of a vertex attribute
    // @param index: Index of vertex attribute in the shader (aka location)
    // @param offset: Offset of the attribute data of first vertex within the specified buffer
    // @param type: GLSL element type of the vertex attribute
    // @param arrayCount: Element array count, e.g. 5 if type was int[5]
    // @param normalized: If type is fixed-point, normalize data to float in ranges [0.0, 1.0] or [-1.0, 1.0] (depending on signedness of type)
    // @param divisor: Number of instances that will pass between advancing of the attribute data
    //          = 0 -> attribute data will advance once per vertex
    //          > 0 -> attribute data will advance once per "divisor" instances
    //          Other than 0 and 1, you can have up to two unique divisors per VBO (HW limit)
    bool setVertexAttrib(u32 index, u32 offset, VarType type, u32 arrayCount = 1, bool normalized = false, u32 divisor = 0);

    // Build the structure of this VBO
    //! *Must* be called after all vertex attributes have been set
    void build(sead::Heap* heap = nullptr);

    // Bind buffer data
    // As long as this VBO exists, user must *not* free the buffer data passed
    // @param stride: Number of bytes between each vertex
    void bindBufferData(const void* bufferData, u32 size, u32 stride);

    // Get the data bound to the specified buffer through this VBO
    const void* getBufferData() const;

    // Bind the VBO
    //! Must be done *after* shader is bound
    void bind() const;

private:
    u32 bufferIndex;
    const void* bufferData;
    u32 bufferSize;
    u32 stride;
    GX2AttribStream streams[MAX_STREAM_COUNT];
    u32 streamUsedCount;
    bool built;
    GX2FetchShader fetchShader;
    u32 fetchShaderBufferSize;
    u8* fetchShaderBuffer;
};
