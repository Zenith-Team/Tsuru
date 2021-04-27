#pragma once

#include "sead.h"
#include "dynamic_libs/gx2_types.h"

template <class T>
struct List {
    u32 count;
    T* list;
};

namespace agl {

namespace lyr {

enum DisplayType { };

class DebugInfo {
public:
    u8 _0[0x390];
};

class Layer : public sead::IDisposer {
public:
    u32 _10;
	sead::Viewport viewPort1;
	sead::Viewport viewPort2;
	u32 _44;
	u32 _48;
	u32 _4C;
	u32 _50;
	u32 _54;
	u32 _58;
	u32 _5C;
	u32 _60;
	u32 _64;
	u32 _68;
	float _6C;
	float _70;
	float _74;
	float _78;
	float _7C;
	sead::ListNode node;
	u32 _88;
	DebugInfo debugInfo;
};

class RenderInfo {
public:
    s32 step;
    DisplayType displayType;
    sead::FrameBuffer* frameBuffer;
    u32 _C;
    Layer* layer;
    void* _14;
    sead::Projection* projection;
    sead::Viewport* viewport;
    DisplayList* displaylist;
    u32 _24;
};


}

class DisplayList {
public:
    DisplayList();
	virtual ~DisplayList();

    u32 _0;
	u32 _4;
	u32 _8;
};

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
    DisplayList displayList;
    List<void> _14;
    List<void> uniformBlocks;
    List<void> _24;
    List<void> samplerBlocks;
    VertexShader vertexShader;
    FragmentShader fragmentShader;
    GeometryShader geometryShader;
    u32 info;
};

class ShaderProgramArchive : public sead::IDisposer {
public:
    ShaderProgramArchive();
    ~ShaderProgramArchive();

    s32 searchShaderProgramIndex(sead::SafeStringBase<char>* name);

    void* resBinaryShaderArchive;
    u32 _14;
    List<ShaderProgram> programs;
    u32 _20;
	u32 _24;
	u16 _28;
	u16 _2A;
	u32 _2C;
	u32 _30;
	u32 _34;
	u32 _38;
	u32 _3C;
	u32 _40;
	u32 _44;
	u32 _48;
};

enum TextureType     { };
enum TextureFormat   { };
enum MultiSampleType { };

class TextureData {
public:
    TextureData();

    void invalidateGPUCache();
    void initialize(TextureType, TextureFormat, u32 width, u32 height, u32 depth, u32 mipLevelNum, MultiSampleType);
    void loadGTX(void* data, u32);

    virtual void vf0C() deleted;

    TextureFormat format;
    GX2Surface surface;
    u32 width;
	u32 height;
	u32 depth;
	u32 size;
	u32 compSel1;
	u32 compSel2;
	u32 compSel3;
	u32 compSel4;
};

class TextureSampler {
public:
    void applyTextureData(agl::TextureData*);
};

class RenderTargetColor {
public:
    RenderTargetColor();

    void invalidateGPUCache();
    void applyTextureData(agl::TextureData*);

    TextureData textureData;
    u32 _9C;
    u32 vieMip;
    u32 viewFirstSlice;
    u8 _A8;
    u8 _A9;
    u8 _AA;
    u8 _AB;
    u32 auxBufferSize;
    u32 auxBufferAlign;
    u32 _B4;
    GX2ColorBuffer colorBuffer;
};

class RenderTargetDepth {
public:
    RenderTargetDepth();

    void invalidateGPUCache();
    void applyTextureData(agl::TextureData*);

    TextureData textureData;
	u8 _9C;
	u32 _A0;
	u32 _A4;
	u32 _A8;
	u32 _AC;
	u32 _B0;
	GX2DepthBuffer depthBuffer;
};

class RenderBuffer : public sead::IDisposer {
public:
    RenderBuffer();
    RenderBuffer(Vec2* size, f32, f32, f32, f32);
    virtual ~RenderBuffer();

    void clear(u32, u32 flags, sead::Color4f* color, u32 stencilValue, f32 depthValue);

    sead::FrameBuffer frameBuffer;
    RenderTargetColor* targetColors[8];
    RenderTargetDepth* targetDepth;
};


}
