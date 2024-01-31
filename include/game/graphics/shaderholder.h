#pragma once

#include "heap/seadDisposer.h"
#include "agl/shaderprogram.h"
#include "agl/shaderprogramarchive.h"

class ShaderHolder
{
    SEAD_SINGLETON_DISPOSER(ShaderHolder);

public:
    const agl::ShaderProgramArchive* getShaderArchive(const sead::SafeString& filename) const;
    const agl::ShaderProgramArchive* getNw4fShaderArchive() const;
    const agl::ShaderProgram* getNw4fBasicShaderProgram() const;

    u8 _10[0xCA4-0x10];
};
static_assert(sizeof(ShaderHolder) == 0xCA4);
