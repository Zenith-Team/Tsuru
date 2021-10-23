#include <game/actor/stage/stageactor.h>
#include <game/collision/solid/solidontopcollider.h>
#include <game/graphics/model/platformmodel.h>
#include <game/graphics/drawmgr.h>
#include <math.h>
#include <game/util.h>
#include <game/level/levelcamera.h>
#include <game/tilemgr.h>

class WavePlatform : public StageActor {
public:
    WavePlatform(const ActorBuildInfo* buildInfo);
    virtual ~WavePlatform() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    bool updateWaveTargets();
    void updateModel();

    PlatformModel model;
    u8 width;
    f32 targetPos;
    f32 targetRot;
    bool offscreen;
};

const ActorInfo actorInfo = {
    Vec2i(0, 0), Vec2i(0, 0), Vec2i(0, 0), 0, 0, 0, 2, 0
};

const Profile WavePlatformProfile(&WavePlatform::build, ProfileID::WavePlatform, "WavePlatform", &actorInfo);
PROFILE_RESOURCES(ProfileID::WavePlatform, "lift_han_wood", "lift_han_stone", "lift_kinoko_yoko", "lift_han_spin", "lift_kinoko_shiso", "lift_han_sky");

WavePlatform::WavePlatform(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
    , model()
{ }

Actor* WavePlatform::build(const ActorBuildInfo* buildInfo) {
    return new WavePlatform(buildInfo);
}

u32 WavePlatform::onCreate() {
    this->width = this->settings1 & 0xF; // Nybble 12
    if (this->width < 2) this->width = 2;

    this->model.create(this->width, this->settings1 >> 0x1C & 0xF);

    this->offscreen = true;

    this->updateModel();

    return this->onExecute();
}

u32 WavePlatform::onExecute() {
    if (!this->updateWaveTargets()) {
        this->offscreen = true;
        return 1;
    }

    /*
        To prevent a sudden jump in height and tilt, set a target and move towards it by a certain amount
        However, if the platform is offscreen, it can move to a Y position of -8192. In that case, immediately change its values to their targets
    */

    if (this->offscreen) {
        this->position.y = this->targetPos;
        this->rotation.z = this->targetRot;
    } else {
        moveFloatTo(this->position.y, this->targetPos, 2.0);
        moveValueTo(this->rotation.z, this->targetRot, fixDeg(2.0f));
    }

    this->updateModel();
    
    return 1;
}

u32 WavePlatform::onDraw() {
    this->model.draw();
    
    return 1;
}

bool WavePlatform::updateWaveTargets() {
    // Get wave floats index
    s32 index = (s32)((this->position.x - LevelCamera::instance()->_28[0].left) * 0.5 + 0.5);

    if (index < 10 - 144 || index >= 1190 + 1140)
        return 0;

    if (index < 10)
        index += 144;

    if (index >= 1190)
        index -= 144;

    if (TileMgr::instance()->waveFloats[2][index + 10] == -8192)
        index -= 144;

    // Take an average to soften the impact (position)
    f32 left = TileMgr::instance()->waveFloats[2][index - 10];
    f32 middle = TileMgr::instance()->waveFloats[2][index];
    f32 right = TileMgr::instance()->waveFloats[2][index + 10];

    this->targetPos = (left + middle + right) / 3.0f + 4.0f;

    if (left == -8192 || middle == -8192 || right == -8192 || left == 0 || middle == 0 || right == 0)
        return false;

    // Take an average to soften the impact (rotation)
    f32 ydiff1 = middle - left;
    f32 ydiff2 = right - middle;
    f32 ydiffavg = (ydiff1 + ydiff2) / 2;
    this->targetRot = (u32)(atan2f(ydiffavg, 20.0f) / M_2_PI * 0x100000000);

    return true;
}

void WavePlatform::updateModel() {
    Vec3f modelPos(this->position.x - this->width * 8.0f, this->position.y, this->position.z);
    this->model.rotation.z = this->rotation.z;
    this->model.update(modelPos, this->width * 16.0f);
}
