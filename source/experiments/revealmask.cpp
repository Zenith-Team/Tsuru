#include <game/graphics/tilerenderer.h>

namespace sead {
class GraphicsContextMRT {  //! This is a temporary definition 
                            // TODO: Properly RE this class and define it in a header
public:
    class BlendExpression {
    public:
        u32 colorSrcBlend;
        u32 alphaSrcBlend;
        u32 colorDstBlend;
        u32 alphaDstBlend;
        u32 colorCombine;
        u32 alphaCombine;
        
        BlendExpression();
    };

    bool depthEnable;
    bool depthWriteEnable;
    u32 depthFunc;

    u32 _8;
    u32 blendEnableMask;
    BlendExpression blendExpressions[8];

    Color4f color;
    bool alphaTestEnable;
    u32 alphaFunc;

    f32 ref;
    u32 targetChannelMasks;

    bool stencilEnable;
    u32 stencilFunc;
    u32 writeMask;
    u32 preMask;
    u32 stencilFail;
    u32 stencilZFail;
    u32 stencilZPass;

    u32 _10C;
    u32 _110;
    u32 _114;

    GraphicsContextMRT();

    void apply();

    virtual void vf0C(); //deleted
};

	class GraphicsContext { //! TODO: Same as above
		public:
		bool depthEnable;
		bool depthWriteEnable;
		u32 depthFunc;
		u32 cullRelated;
		
		bool blendEnable;
		u32 colorSrcBlend;
		u32 alphaSrcBlend;
		u32 colorDstBlend;
		u32 alphaDstBlend;
		u32 colorCombine;
		u32 alphaCombine;
		
		Color4f color;
		
		bool alphaTestEnable;
		u32 alphaFunc;
		float ref;
		
		u8 _44;
		u8 _45;
		u8 _46;
		u8 _47;
		
		bool stencilEnable;
		u32 stencilFunc;
		u32 writeMask;
		u32 preMask;
		u32 stencilFail;
		u32 stencilZFail;
		u32 stencilZPass;
		u32 polygonModeFront;
		u32 polygonModeBack;
		bool polyOffsetFrontEnable;
		bool polyOffsetBackEnable;
		bool polyLineOffsetEnable;
		
		GraphicsContext();
		
		void apply();
		
		virtual void vf0C(); //deleted
	};

}

class TsuruTileRenderer : public TileRenderer {

    // This class replaces multiple aspects of the game's TileRenderer class

    /*
        * Attempted implementation of Newer U's "NewerBGRenderer"
        * Draws Layer 1 tiles with a reveal mask similar to how the game draws Layer 0 tiles with spotlight masks
        * Uses a custom shader found in content/Common/shader/shaderfb.szs 
        * Full credits to Kinnay for the original version :)
    */

public:
    TsuruTileRenderer();
    ~TsuruTileRenderer();

    void init(sead::Heap* heap); // Fake override
    void initRevealMaskFrameBuffer(const agl::lyr::RenderInfo& renderInfo);
    void initLayer1FrameBuffer(const agl::lyr::RenderInfo& renderInfo);

    void drawRevealMasks(const agl::lyr::RenderInfo& renderInfo);
    void drawTilesWithRevealMasks(const agl::lyr::RenderInfo& renderInfo);

    void renderLayer1(const agl::lyr::RenderInfo& renderInfo); // Fake override

    void revealMaskRenderStep(const agl::lyr::RenderInfo& renderInfo);

    void freeLayerMaskTextureData();

    static void initShaders(agl::ShaderProgramArchive& archive, sead::Heap* heap); // Fake override

    agl::ShaderProgram* revealMaskShader;

    agl::TextureData layer1TextureData;
    agl::RenderTargetColor layer1TargetColor;
    agl::RenderBuffer layer1RenderBuffer;

    agl::TextureData revealMaskTextureData;
    agl::RenderTargetColor revealMaskTargetColor;
    agl::RenderBuffer revealMaskRenderBuffer;

    TileMaskList revealMasks;

    bool revealMasksEnabled;
};

static Vec2f resolution(1280.0f, 720.0f);

TsuruTileRenderer::TsuruTileRenderer()
    : TileRenderer()
    , layer1RenderBuffer(resolution, 0.0f, 0.0f, 1280.0f, 720.0f)
    , revealMaskRenderBuffer(resolution, 0.0f, 0.0f, 1280.0f, 720.0f)
{ }

TsuruTileRenderer::~TsuruTileRenderer() {
    if (this->layer1TextureData.surface.imageData)
        delete this->layer1TextureData.surface.imageData;
    
    if (this->revealMaskTextureData.surface.imageData)
        delete this->revealMaskTextureData.surface.imageData;
}

void TsuruTileRenderer::init(sead::Heap* heap) {
    TileRenderer::init(heap);
    this->revealMasks.init(heap);

    // Get the shader
    sead::SafeString programName = "reveal_mask_program";
    u32 programIndex = this->shaderArchive->searchShaderProgramIndex(programName);
    this->revealMaskShader = &this->shaderArchive->programs.buffer[programIndex];

    // Initialize texture data
    this->layer1TextureData.initialize_(0x1, 0x1D, 1280, 720, 1, 1, 0x0);
    this->layer1TextureData.surface.imageData = operator new(this->layer1TextureData.surface.imageSize, 0, this->layer1TextureData.surface.align);

    this->revealMaskTextureData.initialize_(0x1, 0x1D, 1280, 720, 1, 1, 0x0);
    this->revealMaskTextureData.surface.imageData = operator new(this->revealMaskTextureData.surface.imageSize, 0, this->revealMaskTextureData.surface.align);
}

void TsuruTileRenderer::initRevealMaskFrameBuffer(const agl::lyr::RenderInfo& renderInfo) {
    // The mask textures should be drawn on this texture
    // Attach it to a buffer and bind it
    this->revealMaskTargetColor.applyTextureData(this->revealMaskTextureData);
    this->revealMaskRenderBuffer.targetColors[0] = &this->revealMaskTargetColor;
    this->revealMaskRenderBuffer.frameBuffer.bind();

    sead::GraphicsContext context;
    context.blendEnable = true;
    context.depthWriteEnable = false;
    context.depthEnable = false;
    context.apply();

    // TODO: Check if should use reveal masks here conditionally
    sead::Color4f red(1.0f, 0.0f, 0.0f, 0.0f);
    this->revealMaskRenderBuffer.clear(0, 1, red, 1.0f, 0);
}

void TsuruTileRenderer::initLayer1FrameBuffer(const agl::lyr::RenderInfo& renderInfo) {
    // Apply the texture data to a render target
    this->layer1TargetColor.applyTextureData(this->layer1TextureData);

    // Apply the render target to a render buffer and bind it
    this->layer1RenderBuffer.targetColors[0] = &this->layer1TargetColor;
    this->layer1RenderBuffer.frameBuffer.bind();

    // Everything will be drawn onto the layer 1 texture data now

    sead::GraphicsContextMRT context;
    context.blendEnableMask &= ~3;
    context.targetChannelMasks = 0xFF;
    context.apply();

    sead::Color4f black(0.0f);

    this->layer1RenderBuffer.clear(0, 1, black, 1.0f, 0);
}

void TsuruTileRenderer::drawRevealMasks(const agl::lyr::RenderInfo& renderInfo) {
    sead::GraphicsContext context;
    context.blendEnable = true;
    context.depthEnable = false;
    context.depthWriteEnable = false;
    context.apply();

    // Render the mask textures onto our texture
    const Mtx44& matrix = renderInfo.projection->getDeviceProjectionMatrix();
    this->revealMasks.draw(*renderInfo.camera, matrix);

    this->revealMaskTargetColor.invalidateGPUCache();
    this->revealMaskTextureData.invalidateGPUCache();

    // Bind the original frame buffer, we're going to draw to the screen now
    renderInfo.renderBuffer->frameBuffer.bind();
}

void TsuruTileRenderer::drawTilesWithRevealMasks(const agl::lyr::RenderInfo& renderInfo) {
    // Using the function that renders layer 0 tiles with spotlight masks, replace the texture data and shader with our own
    agl::TextureData* originalMaskTextureData = this->maskTextureData;
    agl::TextureData* originalLayer0TextureData = this->layer0TextureData;
    agl::ShaderProgram* originalShaderProgram = this->spotlightMaskShader;

    this->revealMasksEnabled = true;
    this->maskTextureData = &this->revealMaskTextureData;
    this->layer0TextureData = &this->layer1TextureData;
    this->spotlightMaskShader = this->revealMaskShader;
    
    this->drawTilesWithSpotlightMasks(renderInfo);

    // Restore original texture data and shader
    this->revealMasksEnabled = false;
    this->maskTextureData = originalMaskTextureData;
    this->layer0TextureData = originalLayer0TextureData;
    this->spotlightMaskShader = originalShaderProgram;
}

void TsuruTileRenderer::renderLayer1(const agl::lyr::RenderInfo& renderInfo) {
    sead::OrthoProjection projection;
    sead::OrthoProjection* projectionInfo = static_cast<sead::OrthoProjection*>(renderInfo.projection);

    // TODO: Use the param constructor instead
    projection.setNearFarClip(projectionInfo->nearClip, projectionInfo->farClip);
    projection.setTBLR(projectionInfo->top, projectionInfo->bottom, projectionInfo->left, projectionInfo->right);

	sead::GraphicsContextMRT context;
	context.blendEnableMask &= ~3;
	context.alphaTestEnable = true;
	context.ref = 0.0625;
	context.depthEnable = true;
	context.depthWriteEnable = true;
	context.targetChannelMasks = 0xFF;
	context.alphaFunc = 6;
	context.apply();

    this->layer1RenderBuffer.frameBuffer.bind();

    // Since our own frame buffer is bound, tiles will be drawn onto a texture instead of the screen
    this->renderTileLayer(*renderInfo.viewport, projection, EditorTileLayer_1);

    this->layer1TargetColor.invalidateGPUCache();
    this->layer1TextureData.invalidateGPUCache();

    context.targetChannelMasks &= ~0xF0;
    context.apply();

    this->freeTexture(&this->layerDepthTextureData);
    this->freeTexture(&this->layerBufferTextureData);
}

void TsuruTileRenderer::revealMaskRenderStep(const agl::lyr::RenderInfo& renderInfo) {
    // Do a full render cycle
    
    this->initRevealMaskFrameBuffer(renderInfo);
    this->drawRevealMasks(renderInfo);
    this->drawTilesWithRevealMasks(renderInfo);

    this->initSpotlightMaskFrameBuffer(renderInfo);
}

void TsuruTileRenderer::freeLayerMaskTextureData() {
    if (!this->revealMasksEnabled) {
        this->freeTexture(&this->maskTextureData);
        this->freeTexture(&this->layer0TextureData);
    }
}

void TsuruTileRenderer::initShaders(agl::ShaderProgramArchive& archive, sead::Heap* heap) {
    TileRenderer::initShaders(archive, heap);

    // Get the shader
    sead::SafeString programName = "reveal_mask_program";
    u32 programIndex = archive.searchShaderProgramIndex(programName);
    agl::ShaderProgram* revealShader = &archive.programs.buffer[programIndex];

    // Uniform blocks
    revealShader->createUniformBlock(2, heap);
    revealShader->setUniformBlockName(0, "projection[0]");
    revealShader->setUniformBlockName(1, "circle_color");

    // Sampler blocks
    revealShader->createSamplerBlock(2, heap);
    revealShader->setSamplerBlockName(0, "texture_layer0");
    revealShader->setSamplerBlockName(1, "texture_mask");
}

extern "C" void freeLayerMaskTextureData() {
    __asm("mr r3, r30");
    __asm("b freeLayerMaskTextureData__17TsuruTileRendererFv");
}
