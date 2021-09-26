#pragma once

#include <types.h>

namespace agl {

class Shader { // Size: 0xC
public:
    enum ShaderType {
        ShaderType_Vertex = 0,
        ShaderType_Fragment = 1,
        ShaderType_Geometry = 2
    };

public:
    Shader();

    u32 setUp(bool, bool);

    virtual void vf0C();                        // deleted
    virtual ShaderType getShaderType() = 0;
    virtual void vf1C();                        // deleted
    virtual void vf24();                        // deleted

    void* _0;
    void* _4;
};

static_assert(sizeof(Shader) == 0xC, "agl::Shader size mismatch");

class VertexShader : public Shader { // Size: 0xC
public:
    ShaderType getShaderType() override;
};

static_assert(sizeof(VertexShader) == 0xC, "agl::VertexShader size mismatch");

class FragmentShader : public Shader { // Size: 0xC
public:
    ShaderType getShaderType() override;
};

static_assert(sizeof(FragmentShader) == 0xC, "agl::FragmentShader size mismatch");

class GeometryShader : public Shader { // Size: 0xC
public:
    ShaderType getShaderType() override;
};

static_assert(sizeof(GeometryShader) == 0xC, "agl::GeometryShader size mismatch");

}
