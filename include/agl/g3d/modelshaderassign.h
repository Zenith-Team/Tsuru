#pragma once

#include "sead/safestring.h"
#include "sead/heap.h"
#include "agl/shaderlocation.h"
#include "nw/g3d/fnd/fetchshader.h"

namespace nw { namespace g3d {

class MaterialObj;

namespace res {

class ResMaterial;
class ResShape;
class ResSampler;

}

namespace fnd {

class GfxBuffer;

}

} }

namespace agl {

class ShaderProgram;

namespace g3d {

class ModelShaderAttribute {
private:
    class Attribute {
    public:
        Attribute()
            : index(0)
            , name("Undefined")
            , location(0)
        { }

        s32 index;
        sead::SafeString name;
        s16 location;
    };

    static_assert(sizeof(Attribute) == 0x10, "agl::g3d::ModelShaderAttribute::Attribute size mismatch");

public:
    ModelShaderAttribute();
    ~ModelShaderAttribute();

    void create(sead::Heap* heap);
    void clear();

    void bind(const nw::g3d::res::ResMaterial* resMat, const nw::g3d::res::ResShape* resShape, const ShaderProgram* program, bool useResAssign, bool useShaderSymbolID);

    void activateVertexBuffer() const;

    u8 _0;
    u8 vertexBufferNum;
    const nw::g3d::fnd::GfxBuffer* vertexBuffer[16];
    nw::g3d::fnd::GfxFetchShader fetchShader;
};

static_assert(sizeof(ModelShaderAttribute) == 0x6C, "agl::g3d::ModelShaderAttribute size mismatch");

class ModelShaderAssign {
public:
    ModelShaderAssign();
    ~ModelShaderAssign();

    void create(sead::Heap* heap);

    void bind(const nw::g3d::res::ResMaterial* resMat, const ShaderProgram* program, bool useResAssign, bool useShaderSymbolID);
    void bindShaderResAssign(const nw::g3d::res::ResMaterial* resMat, const nw::g3d::res::ResShape* resShape, const ShaderProgram* program, const char* = "Mat");
    void bindShader(const nw::g3d::res::ResMaterial* resMat, const nw::g3d::res::ResShape* resShape, const ShaderProgram* program, const char* = "Mat");

    void pushBackSampler(const nw::g3d::res::ResSampler* resSampler, const SamplerLocation& location);

    void activateMaterialUniformBlock(const nw::g3d::MaterialObj* material) const;
    void activateTextureSampler(const nw::g3d::MaterialObj* material) const;

    void clear_();
    void updateLocation_(const char* uniformBlockName);

    const ShaderProgram* program;
    UniformBlockLocation uniformBlockLocation;
    SamplerLocation samplerLocations[16];
    const nw::g3d::res::ResSampler* resSamplers[16];
    u8 samplerNum;
    ModelShaderAttribute attribute;
};

static_assert(sizeof(ModelShaderAssign) == 0x1C4, "agl::g3d::ModelShaderAssign size mismatch");

} }
