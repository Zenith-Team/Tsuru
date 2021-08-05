#include "game/actor/stage/stageactor.h"
#include "sead.h"
#include "dynlibs/gx2/functions.h"
#include "dynlibs/os/functions.h"
#include "log.h"

struct ShaderGroup {
    GX2FetchShader mFetchShader;
    void* mFetchShaderProgram;
    GX2PixelShader* mPixelShader;
    GX2VertexShader* mVertexShader;
    u32 mNumAttributes;
    GX2AttribStream mAttributes[16];
};

static const f32 PositionData[] =  {
     1.0f, -1.0f, 0.0f, 1.0f,
     0.0f,  1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 1.0f, 1.0f
};

static const f32 ColorData[] = {
    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f
};


class GraphicsActor : public StageActor {
public:
    GraphicsActor(const ActorBuildInfo* buildInfo);
    ~GraphicsActor() { }

    static ActorBase* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onDraw() override;

    void render();
};

const Profile GraphicsActorProfile(&GraphicsActor::build, ProfileID::GraphicsActor, "GraphicsActor", nullptr, 0);

GraphicsActor::GraphicsActor(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
{ }

ActorBase* GraphicsActor::build(const ActorBuildInfo* buildInfo) {
    return new GraphicsActor(buildInfo);
}

u32 GraphicsActor::onCreate() {
    render();

    return 1;
}

u32 GraphicsActor::onDraw() {
    render();

    return 1;
}

void GraphicsActor::render() {
    static bool HasRendered = false;
    if (HasRendered)
        goto renderstep;

    GX2RBuffer positionBuffer = { 0 };
    GX2RBuffer colorBuffer = { 0 };
    void* buffer = nullptr;
    const u8* gshFileData = nullptr;

    sead::FileDevice::LoadArg file;

    file.mPath = "superres/pos_col_shader.gsh";

    gshFileData = sead::FileDeviceMgr::sInstance->tryLoad(file);

    if (!gshFileData)
        return;

    LOG("File data: %s", gshFileData);
    
    positionBuffer.flags = GX2R_RESOURCE_BIND_VERTEX_BUFFER | GX2R_RESOURCE_USAGE_CPU_READ | GX2R_RESOURCE_USAGE_CPU_WRITE | GX2R_RESOURCE_USAGE_GPU_READ;
    positionBuffer.elemSize = 4 * 4;
    positionBuffer.elemCount = 3;
    GX2RCreateBuffer(&positionBuffer);
    buffer = GX2RLockBufferEx(&positionBuffer, 0);
    OSBlockMove(buffer, PositionData, positionBuffer.elemSize * positionBuffer.elemCount, 0);
    GX2RUnlockBufferEx(&positionBuffer, 0);

    colorBuffer.flags = GX2R_RESOURCE_BIND_VERTEX_BUFFER | GX2R_RESOURCE_USAGE_CPU_READ | GX2R_RESOURCE_USAGE_CPU_WRITE | GX2R_RESOURCE_USAGE_GPU_READ;
    colorBuffer.elemSize = 4 * 4;
    colorBuffer.elemCount = 3;
    GX2RCreateBuffer(&colorBuffer);
    buffer = GX2RLockBufferEx(&colorBuffer, 0);
    OSBlockMove(buffer, ColorData, colorBuffer.elemSize * colorBuffer.elemCount, 0);
    GX2RUnlockBufferEx(&colorBuffer, 0);

    goto renderstep;

renderstep:
    HasRendered = true;

    f32* colors = (f32*)GX2RLockBufferEx(&colorBuffer, 0);

    colors[0] = 1.0f;
    colors[1] = colors[1] >= 1.0f ? 0.0f : (colors[1] + 0.01f);
    colors[2] = colors[2] >= 1.0f ? 0.0f : (colors[2] + 0.01f);
    colors[3] = 1.0f;

    colors[4] = colors[4] >= 1.0f ? 0.0f : (colors[4] + 0.01f);
    colors[5] = 1.0f;
    colors[6] = colors[6] >= 1.0f ? 0.0f : (colors[6] + 0.01f);
    colors[7] = 1.0f;

    colors[8] = colors[8] >= 1.0f ? 0.0f : (colors[8] + 0.01f);
    colors[9] = colors[9] >= 1.0f ? 0.0f : (colors[9] + 0.01f);
    colors[10] = 1.0f;
    colors[11] = 1.0f;

    GX2RUnlockBufferEx(&colorBuffer, 0);


}
