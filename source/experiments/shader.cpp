#include "agl/uniformblock.h"
#include "agl/shaderprogramarchive.h"
#include "game/graphics/shaderholder.h"

#include "sead/threadmgr.h"
#include "agl/lyr/renderinfo.h"
#include "log.h"

ASM_BEGIN

.include "macros.S"

.global LayerFunc
LayerFunc:
    SaveVolatileRegisters
    mr r3, r11
    bl layerFunc__FPv
    RestoreVolatileRegisters

    lwz r0, 0x0(r11)
    blr

ASM_END

void layerFunc(void* ptr)
{
    agl::lyr::RenderInfo* renderInfo = (agl::lyr::RenderInfo*)ptr;
    s32 renderStep = renderInfo->renderStepIndex;

    sead::Thread* thread = sead::ThreadMgr::instance()->getCurrentThread();
    //PRINT(thread->getName().cstr(), " ", renderStep);
}

void uniformBlock(agl::UniformBlock* uniformBlock, void* buf, void* loc, u32 offs, u32 size)
{
    //uniformBlock->dcbz();

    static f32 sTime = 0.0f;

    static bool up = true;

    if (up)
        sTime += 0.001f;
    else
        sTime -= 0.001f;

    if (sTime > 1.0f || sTime < 0.0f)
        up = !up;

    sead::Vector3<f32> vec3;
    vec3.x = 0.0f;
    vec3.y = 0.0f;
    vec3.z = sTime;

    sead::Vector4<f32> color4;
    color4.x = sTime;
    color4.y = 0.0f;
    color4.z = 0.0f;
    color4.w = 1.0f;
/* 
    for (u32 i = 0; i < 8; i++)
    {
        //uniformBlock->setVector3f(2, vec3, i); // cLightDiffDir
    }
    for (u32 i = 0; i < 8; i++)
    {
        uniformBlock->setVector4f(3, color4, i); // cLightDiffColor
    }
    for (u32 i = 0; i < 2; i++)
    {
        uniformBlock->setVector4f(4, color4, i); // cAmbColor
    }
    for (u32 i = 0; i < 8; i++)
    {
        uniformBlock->setVector3f(5, vec3, i); // cFogColor
    }
    for (u32 i = 0; i < 8; i++)
    {
        uniformBlock->setFloat(6, 0.1f, i); // cFogStart
    }
    for (u32 i = 0; i < 8; i++)
    {
        //uniformBlock->setFloat(7, sTime, i); // cFogStartEndInv
    }
    for (u32 i = 0; i < 4; i++)
    {
        uniformBlock->setVector4f(8, color4, i);
    }
    for (u32 i = 0; i < 8; i++)
    {
        uniformBlock->setVector3f(9, vec3, i);
    }
    for (u32 i = 0; i < 4; i++)
    {
        uniformBlock->setVector4f(10, color4, i);
    } */

    uniformBlock->flush(false);

    //uniformBlock->setUniform(buf, *(agl::UniformBlockLocation*)loc, offs, size);
}

agl::ShaderMode shaderFunc(agl::ShaderProgram* program, agl::ShaderMode shaderMode)
{
    const agl::ShaderProgramArchive* shaderProgramArchive = ShaderHolder::instance()->getNw4fShaderArchive();
    s32 shaderProgramIdx = shaderProgramArchive->searchShaderProgramIndex("nw4f_basic_shader");

    const agl::ShaderProgram* shaderProgram = &shaderProgramArchive->programs[shaderProgramIdx];

    return program->activate(shaderMode);
}
