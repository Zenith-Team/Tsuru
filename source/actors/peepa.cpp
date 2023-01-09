#include "game/actor/stage/enemy.h"
#include "game/graphics/model/modelnw.h"
#include "game/movementhandler.h"
#include "game/graphics/model/platformmodel.h"
#include "game/collision/solid/polylinecollider.h"
#include "game/collision/collidermgr.h"
#include "game/effect/effect.h"

class Peepa : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(Peepa, Enemy);
public:
    Peepa(const ActorBuildInfo* buildInfo);
    virtual ~Peepa() { }

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    void collisionYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionGroundPound(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionStar(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionPenguinSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionGroundPoundYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionPropellerDrill(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionThrowableObject(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionFireball(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionIceball(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionFireballYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    static HitboxCollider::Info collisionInfo;

    ModelWrapper* peepaModel;
    ModelWrapper* cloudPlatformModel;
    MovementHandler movementHandler;
    PlatformModel platformModel;
    PolylineCollider polylineCollider;
    bool hasPlatform;
    int platformType;
    Vec3f effectScale;
    Vec3f effectOffset;

    DECLARE_STATE(Peepa, Die);
};

CREATE_STATE(Peepa, Die);

REGISTER_PROFILE(Peepa, ProfileID::Peepa);
PROFILE_RESOURCES(ProfileID::Peepa, Profile::LoadResourcesAt::Course, "teren",
"lift_han_sky", // cloud
"lift_han_spin", // bolt platform
"lift_han_stone", // stone
"lift_han_wood"); // wood and wood snow

HitboxCollider::Info Peepa::collisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(8.0f, 8.0f), HitboxCollider::Shape::Rectangle, 5, 0, 0x824F, 0xFFFBFFFF, 0, &Enemy::collisionCallback
};

Peepa::Peepa(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
    , peepaModel(nullptr)
    , cloudPlatformModel(nullptr)
    , movementHandler()
    , hasPlatform(false)
    , platformType()
    , polylineCollider()
    , effectScale(0.7, 0.7, 0.7)
    , effectOffset(0, 0, 0)
{ }


u32 Peepa::onCreate() {
    this->hasPlatform = (eventID1 >> 0x04 & 0xF);   // nybble 1
    this->platformType = (eventID1 & 0xF);          // nybble 2

    if (this->platformType != PlatformModel::Type::Wood && this->platformType != PlatformModel::Type::Stone && this->platformType != PlatformModel::Type::BoltPlatform && this->platformType != PlatformModel::Type::Sky && this->platformType != PlatformModel::Type::WoodSnow)
        this->hasPlatform = false; // invalid platform types simply won't spawn one

    this->peepaModel = ModelWrapper::create("teren", "teren", 6);
    this->peepaModel->playSklAnim("wait");
    this->cloudPlatformModel = ModelWrapper::create("lift_han_sky", "lift_han_sky_S", 2);
    this->cloudPlatformModel->playSklAnim("move00_S");

    this->platformModel.create(PlatformModel::Type::Wood + platformType, 4);

    this->position.y -= 8.0f;
    this->position.x += 8.0f;
    this->scale = .15f;

    this->hitboxCollider.init(this, &Peepa::collisionInfo);
    this->addHitboxColliders();

    if (this->hasPlatform) {
        int t = 1;
        if (this->platformType == PlatformModel::Type::Sky)
            t = 2;

        Vec2f points[2] = { Vec2f(-32.0f / t, 12.0f), Vec2f(32.0f / t, 12.0f) }; // the cloud platform will always be two tiles in length
        PolylineCollider::Info info = { Vec2f(0.0f, 0.0f), 0, 0, points, 0 };
        this->polylineCollider.init(this, info, 2);
        this->polylineCollider.setType(ColliderBase::Type::Solid);

        if (this->platformType == PlatformModel::Type::WoodSnow)
            this->polylineCollider.setSurfaceType(ColliderBase::SurfaceType::Snow);
        else if (this->platformType == PlatformModel::Type::Sky) {
            this->polylineCollider.setSurfaceType(ColliderBase::SurfaceType::Cloud);
        }

        ColliderMgr::instance()->add(&this->polylineCollider);
    }

    u32 movementMask = this->movementHandler.getMaskForMovementType(this->settings2 & 0xFF);    // nybble 20
    this->movementHandler.link(this->position, movementMask, this->movementID);                 // nybble 21-22

    return this->onExecute();
}

u32 Peepa::onExecute() {
    this->movementHandler.execute();
    this->position = this->movementHandler.position;
    Mtx34 peepaMtx;
    Vec3f peepaModelPos = this->position;
    peepaModelPos.y -= this->hasPlatform ? 10.0f : 8.0f;
    peepaMtx.makeRTIdx(this->rotation, peepaModelPos);
    this->peepaModel->setMtx(peepaMtx);
    this->peepaModel->setScale(this->scale);
    this->peepaModel->updateAnimations();
    this->peepaModel->updateModel();

    Mtx34 cloudPlatformMtx;
    Vec3f cloudPlatformPos = this->position;
    cloudPlatformPos.y += 2;
    cloudPlatformPos.z -= 1000; // cloud platform model goes behind the peepa
    cloudPlatformMtx.makeRTIdx(this->rotation, cloudPlatformPos);
    this->cloudPlatformModel->setMtx(cloudPlatformMtx);
    this->cloudPlatformModel->setScale(1);
    this->cloudPlatformModel->updateAnimations();
    this->cloudPlatformModel->updateModel();

    if (this->hasPlatform) {
        Vec3f platformPos = this->position;
        platformPos.y += 4;
        platformPos.x -= 32;
        platformPos.z -= 1000; // platform goes behind the peepa
        this->polylineCollider.rotation = this->rotation.z;
        this->polylineCollider.execute();
        if (this->platformType != PlatformModel::Type::Sky) {
            this->platformModel.update(platformPos, platformModel.width * 16);
        }
    }

    return 1;
}

u32 Peepa::onDraw() {
    this->peepaModel->draw();

    if (this->platformType == PlatformModel::Type::Sky)
        this->cloudPlatformModel->draw();
    else
        this->platformModel.draw();

    return 1;
}

void Peepa::collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    if (!this->hasPlatform)
        this->damagePlayer(hcSelf, hcOther);
}

void Peepa::collisionYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    if (!this->hasPlatform)
        this->damagePlayer(hcSelf, hcOther);
}

bool Peepa::collisionStar(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    if (!this->hasPlatform)
        doStateChange(&Peepa::StateID_Die);

    return 1;
}

bool Peepa::collisionGroundPound(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    if (!this->hasPlatform)
        this->damagePlayer(hcSelf, hcOther);

    return 1;
}

bool Peepa::collisionSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    if (!this->hasPlatform)
        this->damagePlayer(hcSelf, hcOther);

    return 1;
}

bool Peepa::collisionPenguinSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    if (!this->hasPlatform)
        this->damagePlayer(hcSelf, hcOther);

    return 1;
}

bool Peepa::collisionGroundPoundYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    if (!this->hasPlatform)
        this->damagePlayer(hcSelf, hcOther);

    return 1;
}

bool Peepa::collisionPropellerDrill(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    if (!this->hasPlatform)
        this->damagePlayer(hcSelf, hcOther);

    return 1;
}

bool Peepa::collisionThrowableObject(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    return 1;
}

bool Peepa::collisionFireball(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    return 1;
}

bool Peepa::collisionIceball(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    return 1;
}

bool Peepa::collisionFireballYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    if (!this->hasPlatform)
        doStateChange(&Peepa::StateID_Die);
    return 1;
}

/** STATE: Die */

void Peepa::beginState_Die() {
    Vec3f effectOrigin(this->position.x, this->position.y, 4500.0f);
    Vec3f effectPos(effectOrigin + this->effectOffset);
    Effect::spawn(RP_Jugemu_CloudDisapp, &effectPos, nullptr, &this->effectScale);
    this->isDeleted = true;
}

void Peepa::executeState_Die() {

}

void Peepa::endState_Die() {

}
