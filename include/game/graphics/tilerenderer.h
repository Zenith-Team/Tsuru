#pragma once

#include <sead/idisposer.h>
#include <sead/safestring.h>

#include <agl/texturedata.h>
#include <agl/lyr/renderinfo.h>
#include <agl/shaderprogramarchive.h>
#include <agl/utl/debugtexturepage.h>
#include <agl/vertexbuffer.h>
#include <agl/vertexattribute.h>
#include <agl/indexstream.h>
#include <agl/texturesampler.h>
#include <agl/shaderprogram.h>
#include <agl/rendertargetcolor.h>
#include <agl/rendertargetdepth.h>
#include <agl/renderbuffer.h>

class TileRenderer { // Size: 0x12AFC
    SEAD_SINGLETON_DISPOSER(TileRenderer)

public:
    enum EditorTileLayer { // Converts tile layer number from editor format to internal format
        EditorTileLayer_0 = 2,
        EditorTileLayer_1 = 0,
        EditorTileLayer_2 = 1
    };

    enum InternalTileLayer { // Converts tile layer number from internal format to editor format
        InternalTileLayer_0 = 1,
        InternalTileLayer_1 = 2,
        InternalTileLayer_2 = 0
    };

public:
    struct TileRendererCount { // Size: 0x10
        u8 _0[0x10];    // Unknown values
    };

    class TileMaskList { // Size: 0x5110
    public:
        struct MaskInfo {
            Vec2f position;
            f32 transparency;
            Vec2f texCoords;
        };
    
    public:
        TileMaskList();
        virtual ~TileMaskList();

        void init(sead::Heap* heap);
        void add(MaskInfo&, MaskInfo&, MaskInfo&, agl::TextureData& texture, u32, u32);
        void draw(const sead::Camera& camera, const Mtx44& cameraMatrix);

        u8 _0[0x510C];  // TODO: I'll do this later, I've had enough for tonight
    };

public:
    TileRenderer();
    ~TileRenderer();

    void init(sead::Heap* heap);
    void initSpotlightMaskFrameBuffer(const agl::lyr::RenderInfo& renderInfo);

    void update();

    void registerTile(u32, void*, u32); // TODO: Verify these params as they are guesses

    void drawSpotlightMasks(const agl::lyr::RenderInfo& renderInfo);
    void drawTilesWithSpotlightMasks(const agl::lyr::RenderInfo& renderInfo);

    void renderSingleTile(u32 tileLayer, u32 tile, sead::OrthoProjection& projection);    // TODO: Confirm function and second parameter names

    void renderLayer0(const agl::lyr::RenderInfo& renderInfo);    // Renders editor layer 0, internal layer 2
    void renderLayer1(const agl::lyr::RenderInfo& renderInfo);    // Renders editor layer 1, internal layer 0
    void renderLayer2(const agl::lyr::RenderInfo& renderInfo);    // Renders editor layer 2, internal layer 1

    void renderTileLayer(sead::Viewport& viewport, sead::OrthoProjection& projection, u32 tileLayer);

    static void freeTexture(agl::TextureData** textureData);

    static agl::TextureData* allocTexture(sead::SafeString& name, void**);
    static agl::TextureData* allocDepthTexture(sead::SafeString& name, void**);

    static void initShaders(agl::ShaderProgramArchive& archive, sead::Heap* heap);

    u32 _10;
    u8 _14[0x6094 - 0x14];      // Unknown values
    TileRendererCount tileRendererCounts[4];
    u32 _60D4;
    void* _60D8[2];
    agl::utl::DebugTexturePage _60E0;
    u8 _62BC[0x6300 - 0x62BC];  // Unknown values
    agl::ShaderProgramArchive* shaderArchive;
    u32 _6304;
    u32 _6308;
    u32 _630C;
    agl::VertexBuffer _6310;
    agl::VertexAttribute _64E4;
    agl::IndexStream _65D8;
    agl::TextureSampler* _65F0;
    agl::ShaderProgram* spotlightMaskShader;
    u32 _65F8;
    u8 _65FC[0x6600 - 0x65FC];  // Unknown values
    f32 _6600;
    f32 _6604;
    f32 _6608;
    f32 _660C;
    f32 _6610;
    f32 _6614;
    f32 _6618;
    f32 _661C;
    f32 _6620;
    f32 _6624;
    f32 _6628;
    f32 _662C;
    f32 _6630;
    f32 _6634;
    f32 _6638;
    f32 _663C;
    f32 _6640;
    f32 _6644;
    f32 _6648;
    u16 _664C;
    u16 _664E;
    u16 _6650;
    u16 _6652;
    u16 _6654;
    u16 _6656;
    agl::VertexBuffer _6658;
    agl::VertexAttribute _682C;
    agl::IndexStream _6920;
    agl::TextureSampler* _6938;
    agl::TextureSampler* _693C;
    agl::TextureSampler* _6940;
    agl::TextureData* layer0TextureData;
    agl::RenderTargetColor layer0TextureTargetColor;
    agl::TextureData* layerBufferTextureData;
    agl::RenderTargetColor layerBufferTargetColor;
    agl::TextureData* layerDepthTextureData;
    agl::RenderTargetDepth layerRenderTargetDepth;
    agl::RenderBuffer layer0RenderBuffer;
    agl::RenderTargetColor _6DA8;
    agl::RenderTargetDepth _6EFC;
    agl::TextureData* maskTextureData;
    agl::RenderTargetColor maskTargetColor;
    agl::RenderBuffer maskRenderBuffer;
    u32 _7204;
    agl::RenderTargetColor _7208;
    agl::RenderBuffer _735C;
    u32 _73AC;
    agl::RenderTargetColor _73B0;
    agl::RenderBuffer _7504;
    u32 _7554;
    agl::RenderTargetColor _7558;
    agl::RenderBuffer _76AC;
    u32 _76FC;
    agl::RenderTargetColor _7700;
    agl::RenderBuffer _7854;
    u8 _78A4[0x7968 - 0x78A4];  // Unknown values
    u8 _7968;
    u8 _7969;
    u8 _796A;
    f32 _796C;
    f32 _7970;
    f32 _7974;
    f32 _7978;
    f32 _797C;
    f32 _7980;
    f32 _7984;
    f32 _7988;
    agl::TextureSampler* _798C;
    u8 _7990[0x14][4];    // Array of four CLASS_2693534
    u16 _79E0;
    u16 _79E2;
    u16 _79E4;
    u16 _79E6;
    u16 _79E8;
    u16 _79EA;
    agl::VertexBuffer _79EC;
    agl::VertexAttribute _7BC0;
    agl::IndexStream _7CB4;
    u8 _7CCC[0xC10];    // Is class at 24db424
    TileMaskList tileMasks;
    TileMaskList spotlightMasks;
};

static_assert(sizeof(TileRenderer) == 0x12AFC, "TileRenderer size mismatch");
