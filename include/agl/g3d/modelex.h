#pragma once

#include "sead/heap.h"
#include "agl/shaderprogram.h"
#include "nw/g3d/fnd/buffer.h"
#include "nw/g3d/materialobj.h"
#include "nw/g3d/modelobj.h"
#include "agl/g3d/modelshaderassign.h"

namespace agl { namespace g3d {

class ModelEx;

class MaterialEx {
public:
    MaterialEx();
    ~MaterialEx();

    void init(ModelEx* model, u32 index, sead::Heap* heap);

    void bindShaderResAssign(const ShaderProgram* program, const char* skinMacro, const char** skinValueArray);
    void bindShader(const ShaderProgram* program);

    void replaceUBO(const nw::g3d::fnd::GfxBuffer_t& buffer);
    void fixUpUBO();

    ModelEx* modelEx;
    nw::g3d::MaterialObj* materialObj;
    const ShaderProgram* program;
    nw::g3d::fnd::GfxBuffer_t matBlock;
    bool _20;
};

static_assert(sizeof(MaterialEx) == 0x24, "agl::g3d::MaterialEx size mismatch");

class ModelEx : public nw::g3d::ModelObj {
public:
    ModelEx();
    virtual ~ModelEx();

    void createEx(sead::Heap* heap);
    void destroyEx();

    ModelShaderAssign* shaderAssign;
    MaterialEx* materialEx;
};

static_assert(sizeof(ModelEx) == 0x40, "agl::g3d::ModelEx size mismatch");

} }
