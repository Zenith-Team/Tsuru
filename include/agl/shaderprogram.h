#pragma once

#include <agl/displaylist.h>
#include <agl/shader.h>
#include <sead/buffer.h>
#include <sead/safestring.h>

namespace agl {

class ShaderProgram { // Size: 0x60
public:
    ShaderProgram();
    virtual ~ShaderProgram();

    u32 forceValidate_(bool) const;

    void setShaderGX2() const;
    void setUpForVariation_() const;

    void changeShaderMode(u32 mode);

    void createSamplerBlock(u32 count, sead::Heap* heap);
    void createUniformBlock(u32 count, sead::Heap* heap);

    void setSamplerBlockName(u32 index, const sead::SafeString& name);
    void setUniformBlockName(u32 index, const sead::SafeString& name);

    void updateAttributeLocation() const;
    void updateSamplerLocation() const;
    void updateUniformBlockLocation() const;
    void updateUniformLocation() const;

    u8 flags;                           // _0
    u16 _2;                             // _2
    DisplayList displayList;            // _4
    sead::Buffer<void> _14;             // _14
    sead::Buffer<void> uniformBlocks;   // _1C
    sead::Buffer<void> _24;             // _24
    sead::Buffer<void> samplerBlocks;   // _2C
    VertexShader vertexShader;          // _34
    FragmentShader fragmentShader;      // _40
    GeometryShader geometryShader;      // _4C
    u32 info;                           // _58
};

static_assert(sizeof(ShaderProgram) == 0x60, "agl::ShaderProgram size mismatch");

}
