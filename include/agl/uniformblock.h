#pragma once

#include "agl/shaderlocation.h"
#include "sead/heap.h"
#include "sead/vector.h"

namespace agl {

class UniformBlock {
private:
    struct Member {
        u8 type;
        u16 num;
        u16 offset;
    };

    struct Header {
        Member* member;
        u16 memberNum;
        u16 memberCount;
    };

public:
    enum Type {
        Type_bool,
        Type_int,
        Type_float,
        Type_vec2,
        Type_vec3,
        Type_vec4
    };

public:
    UniformBlock();
    virtual ~UniformBlock();

    void startDeclare(s32 num, sead::Heap* heap);
    void declare(Type type, s32 num);
    void declare(const UniformBlock& block);
    void create(sead::Heap* heap);
    void destroy();
    void dcbz() const;
    void flush(void* memory, bool invalidateGPU) const;
    void flush(bool invalidateGPU) const { flush(this->currentBuffer, invalidateGPU); }
    void flushNoSync(void* memory, bool invalidateGPU) const;
    void flushNoSync(bool invalidateGPU) const { flushNoSync(this->currentBuffer, invalidateGPU); }

    bool setUniform(const void* data, const UniformBlockLocation& location, u32 offset, size_t size) const;
    bool setUniform(const UniformBlockLocation& location) const;

    void setBool(void* memory, s32 index, bool data, s32 arrayIndex = 0) const;
    void setBool(s32 index, bool data, s32 arrayIndex = 0) const;
    void setBool(void* memory, s32 index, const bool* data, s32 arrayNum, s32 arrayIndex = 0) const;
    void setBool(s32 index, const bool* data, s32 arrayNum, s32 arrayIndex = 0) const;

    void setInt(void* memory, s32 index, s32 data, s32 arrayIndex = 0) const;
    void setInt(s32 index, s32 data, s32 arrayIndex = 0) const;
    void setInt(void* memory, s32 index, const s32* data, s32 arrayNum, s32 arrayIndex = 0) const;
    void setInt(s32 index, const s32* data, s32 arrayNum, s32 arrayIndex = 0) const;

    void setFloat(void* memory, s32 index, f32 data, s32 arrayIndex = 0) const;
    void setFloat(s32 index, f32 data, s32 arrayIndex = 0) const
    {
        setData_(currentBuffer, index, &data, arrayIndex, 1);
    }
    void setFloat(void* memory, s32 index, const f32* data, s32 arrayNum, s32 arrayIndex = 0) const;
    void setFloat(s32 index, const f32* data, s32 arrayNum, s32 arrayIndex = 0) const;

    void setVector2f(void* memory, s32 index, const sead::Vector2<f32>& data, s32 arrayIndex = 0) const;
    void setVector2f(s32 index, const sead::Vector2<f32>& data, s32 arrayIndex = 0) const;
    void setVector2f(void* memory, s32 index, const sead::Vector2<f32>* data, s32 arrayNum, s32 arrayIndex = 0) const;
    void setVector2f(s32 index, const sead::Vector2<f32>* data, s32 arrayNum, s32 arrayIndex = 0) const;

    void setVector3f(void* memory, s32 index, const sead::Vector3<f32>& data, s32 arrayIndex = 0) const;
    void setVector3f(s32 index, const sead::Vector3<f32>& data, s32 arrayIndex = 0) const
    {
        setData_(currentBuffer, index, &data, arrayIndex, 1);
    }
    void setVector3f(void* memory, s32 index, const sead::Vector3<f32>* data, s32 arrayNum, s32 arrayIndex = 0) const;
    void setVector3f(s32 index, const sead::Vector3<f32>* data, s32 arrayNum, s32 arrayIndex = 0) const;

    void setVector4f(void* memory, s32 index, const sead::Vector4<f32>& data, s32 arrayIndex = 0) const;
    void setVector4f(s32 index, const sead::Vector4<f32>& data, s32 arrayIndex = 0) const
    {
        setData_(currentBuffer, index, &data, arrayIndex, 1);
    }
    void setVector4f(void* memory, s32 index, const sead::Vector4<f32>* data, s32 arrayNum, s32 arrayIndex = 0) const;
    void setVector4f(s32 index, const sead::Vector4<f32>* data, s32 arrayNum, s32 arrayIndex = 0) const;

    void setData_(void* memory, s32 index, const void* data, s32 arrayIndex, s32 arrayNum) const;

    enum Flags {
        Flag_OwnHeader = 1 << 0,
        Flag_OwnBuffer = 1 << 1
    };

    Header* header;
    u8* currentBuffer;
    u32 blockSize;
    sead::BitFlag8 flag;
};

static_assert(sizeof(UniformBlock) == 0x14, "agl::UniformBlock size mismatch");

}
