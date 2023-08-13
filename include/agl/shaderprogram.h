#pragma once

#include "agl/displaylist.h"
#include "agl/shader.h"
#include "sead/buffer.h"
#include "sead/safestring.h"

namespace agl {

class ShaderProgram { // Size: 0x60
public:
    ShaderProgram();
    virtual ~ShaderProgram();

    ShaderMode activate(ShaderMode shaderMode, bool useDL = true) const;

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

    class SharedData : public sead::INamable
    {
        
    };

    u8 flags;                           // 0
    u16 _2;                             // 2
    DisplayList displayList;            // 4
    sead::Buffer<u32> _14;              // 14  //? What is the template param for these?
    sead::Buffer<u32> uniformBlocks;    // 1C  //? What is the template param for these?
    sead::Buffer<u32> _24;              // 24  //? What is the template param for these?
    sead::Buffer<u32> samplerBlocks;    // 2C  //? What is the template param for these?
    VertexShader vertexShader;          // 34
    FragmentShader fragmentShader;      // 40
    GeometryShader geometryShader;      // 4C
    SharedData* sharedData;                           // 58
};

static_assert(sizeof(ShaderProgram) == 0x60, "agl::ShaderProgram size mismatch");

}
