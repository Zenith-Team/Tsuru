#include "game/actor/stage/stageactor.h"
//#include "game/graphics/model/modelnw.h"
#include "game/graphics/model/platformmodel.h"
#include "log.h"
#include "game/collision/solid/polylinecollider.h"
#include "game/collision/collidermgr.h"
#include "game/level/levelcamera.h"
#include "game/tilemgr.h"
#include "tsuru/utils.h"
#include "sead/mathcalccommon.h"

class WavePlatform : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(WavePlatform, StageActor);

public:
    WavePlatform(const ActorBuildInfo* buildinfo);
    virtual ~WavePlatform() { }

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    f32 targetpos;
    u32 targetrot;
    bool offscreen;
    u8 width;

    bool updateWaveTargets();

    PlatformModel platform;
    PolylineCollider collider;
    LevelCamera levelCamera;
};

REGISTER_PROFILE(WavePlatform, ProfileID::WavePlatform);
PROFILE_RESOURCES(ProfileID::WavePlatform, Profile::LoadResourcesAt::Course, "lift_han_wood", "lift_han_stone", "lift_kinoko_yoko", "lift_han_spin", "lift_kinoko_shiso", "lift_han_sky");

WavePlatform::WavePlatform(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
    , platform()
    , collider()
    , levelCamera()
    , targetpos()
    , targetrot()
    , offscreen()
    , width()
{}

u32 WavePlatform::onCreate() {
    width = settings1 & 0xF;
    if (width < 2) {
        width = 2;
    }
    Vec3i nullvec3i = Vec3i(0, 0, 0);
    Vec3f nullvec3f = Vec3f(0, 0, 0);

    platform.position = this->position;

    platform.create((settings1 >> 0x18 & 0xF), width);
    platform.rotation = nullvec3i;
    platform._A0 = nullvec3f;
    platform.init();

    Vec2f points[2] = { Vec2f(4.0 - platform.width * 8.0, 8.0), Vec2f(-4.0 + platform.width * 8.0, 8.0) };

	PolylineCollider::Info collisionInfo = {0, 0, 0, points, 0 };

    this->collider.init(this, collisionInfo, 2);
    this->collider.setType(ColliderBase::Type::Solid);
    ColliderMgr::instance()->add(&this->collider);

    Vec3f platpos = Vec3f(this->position.x - width * 8, this->position.y, this->position.z);
    platform.position = platpos;
    platform.update(platform.position, platform.width * 16.0);

    offscreen = true;
    onExecute();

    return 1;
}

u32 WavePlatform::onExecute() {
    /*if (!updateWaveTargets()) {
        offscreen = true;
        return 1;
    }*/

    /*if (offscreen) {
        //this->position.y = targetpos;
        //this->rotation.z = targetrot;
        offscreen = false;
    } else {
        sead::Mathf::chase(&this->position.y, targetpos, 2.0);
        sead::Mathu::chase(&this->rotation.z, targetrot, 0x01800000);
    }*/
    
    updateWaveTargets();
    sead::Mathf::chase(&this->position.y, targetpos, 2.0);
    sead::Mathu::chase(&this->rotation.z, targetrot, 0x01800000);

    this->collider.rotation = rotation.z;
    this->collider.execute();
    Vec3f platpos = Vec3f(this->position.x - width * 8, this->position.y, this->position.z);
    platform.position = platpos;
    platform.rotation.z = rotation.z;
    platform.update(platform.position, platform.width * 16.0);
    return 1;
}

u32 WavePlatform::onDraw() {
    platform.draw();
    return 1;
}

bool WavePlatform::updateWaveTargets() {
    float leftedge = LevelCamera::instance()->_28[0].left;

    s32 index = (s32)((this->position.x - leftedge) * 0.5 + 0.5);
    if (index < 10 - 144 || index >= 1190 + 1140) return false;
	
	if (index < 10) index += 144;
	if (index >= 1190) index -= 144;

    if (TileMgr::instance()->waveFloats[index + 10][1] == f32(-8192)) {
        index -= 144;
    }

    // God this is painful

    f32 ypos_1, ypos_m, ypos_r;
    ypos_m = TileMgr::instance()->waveFloats[index][1];
    ypos_1 = TileMgr::instance()->waveFloats[index - 10][1];
    ypos_r = TileMgr::instance()->waveFloats[index + 10][1];

    targetpos = (ypos_1 + ypos_m + ypos_r) / 3 + 4.0;

    if (ypos_m == -8192 || ypos_1 == -8192 || ypos_r == -8192 || ypos_m == 0 || ypos_1 == 0 || ypos_r == 0) return 0;

    // Newer U code is shit ngl. NEVER AGAIN.

    f32 ydiff1 = ypos_m - ypos_1;
	f32 ydiff2 = ypos_r - ypos_m;
	f32 ydiffavg = (ydiff1 + ydiff2) / 2;
	targetrot = (u32)(atan2f(ydiffavg, 20.0) / (2 * M_PI) * 0x100000000);

	return true;
}