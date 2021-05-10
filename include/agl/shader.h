#pragma once

#include "types.h"

namespace agl {

class Shader {
public:
    Shader();

    virtual void vf0C() deleted;
	virtual int getShaderType() = 0;
	virtual void vf1C() deleted;
	virtual void vf24() deleted;

    void* gx2Struct;
    void* compileInfo;
};

class VertexShader   : public Shader { s32 getShaderType(); };
class FragmentShader : public Shader { s32 getShaderType(); };
class GeometryShader : public Shader { s32 getShaderType(); };

}

#include "agl/shader/shaderprogram.h"
