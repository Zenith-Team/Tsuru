#include "actor/stageactor.h"

#include "log.h"
#include "math.h"
#include "misc.h"
#include "level.h"
#include "drawmgr.h"
#include "tilemgr.h"

class WavePlatform : public StageActor {
public:
    WavePlatform(const ActorBuildInfo* buildInfo);
    virtual ~WavePlatform() { }

    static BaseActor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void updateModel();
    bool updateWaveTargets();

    ModelWrapper* model;

    f32 targetPos;
    u32 targetRot;
};

const Profile WavePlatformProfile(&WavePlatform::build, ProfileId::Sprite470, "WavePlatform", nullptr, 0);
PROFILE_RESOURCES(ProfileId::Sprite470, "star_coin");

WavePlatform::WavePlatform(const ActorBuildInfo* buildInfo) : StageActor(buildInfo) { }

BaseActor* WavePlatform::build(const ActorBuildInfo* buildInfo) {
    return new WavePlatform(buildInfo);
}

u32 WavePlatform::onCreate() {
    model = ModelWrapper::create("star_coin", "star_coinA");

    updateModel();

    return 1;
}

u32 WavePlatform::onExecute() {
    LOG("targetPos: %x", targetPos);
    LOG("targetRot: %x", targetRot);
    LOG("pos: %x", position.y);
    LOG("rot: %x", rotation.z);
    updateWaveTargets();
	position.y = targetPos;
	rotation.z = targetRot;
    //moveFloatTo(&position.y, targetPos, 2.0);
    //moveValueTo(&rotation.z, targetRot, 0x01800000);

    return 1;
}

u32 WavePlatform::onDraw() {
    DrawMgr::instance->drawModel(model);

    return 1;
}

void WavePlatform::updateModel() {
    Mtx34 mtx;
    mtx.rotateAndTranslate(rotation, position);

    model->setMtx(mtx);
    model->setScale(scale);
    model->updateModel();
}

bool WavePlatform::updateWaveTargets() {
    LOG("Wave targets updated");
    f32 leftEdge = LevelCamera::instance->someRects[0].left;

    s32 index = (s32)((position.x - leftEdge) * 0.5 + 0.5);

    if (index < 10 - 144 || index >= 1190 + 1140) return 0;
	
	if (index < 10) index += 144;
	if (index >= 1190) index -= 144;
	
	if (TileMgr::instance->waveFloats2[index + 10] == -8192) index -= 144;

    f32 ypos_l, ypos_m, ypos_r;
	ypos_m = TileMgr::instance->waveFloats2[index];
	ypos_l = TileMgr::instance->waveFloats2[index - 10];
	ypos_r = TileMgr::instance->waveFloats2[index + 10];

    targetPos = (ypos_l + ypos_m + ypos_r) / 3 + 4.0;

    if (ypos_m == -8192 || ypos_l == -8192 || ypos_r == -8192 || ypos_m == 0 || ypos_l == 0 || ypos_r == 0) return 0;

    f32 ydiff1 = ypos_m - ypos_l;
	f32 ydiff2 = ypos_r - ypos_m;
	f32 ydiffavg = (ydiff1 + ydiff2) / 2;
	targetRot = (u32)(atan2(ydiffavg, 20.0) / (2 * M_PI) * 0x100000000);

    return 1;
}
