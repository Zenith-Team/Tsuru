#pragma once

#include "sead.h"
#include "types.h"
#include "agl/shader.h"
#include "agl/lyr/display.h"

namespace agl {

class ShaderProgram {
public:
    ShaderProgram();
    virtual ~ShaderProgram();

    void createUniformBlock(s32 count, sead::Heap* heap);
    void setUniformBlockName(s32 index, sead::SafeStringBase<char>* name);

    void createSamplerBlock(s32 count, sead::Heap* heap);
    void setSamplerBlockName(s32 index, sead::SafeStringBase<char>* name);

    u8 flags;
	u8 _1;
	u16 _2;
    lyr::DisplayList displayList;
    List<void> _14;
    List<void> uniformBlocks;
    List<void> _24;
    List<void> samplerBlocks;
    VertexShader vertexShader;
    FragmentShader fragmentShader;
    GeometryShader geometryShader;
    u32 info;
};

}
