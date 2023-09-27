#include "game/actor/stage/enemy.h"
#include "game/graphics/model/modelnw.h"
#include "game/actor/stage/playerbase.h"
#include "game/playermgr.h"
#include "game/actor/actormgr.h"
#include "game/direction.h"
#include "game/effect/effect.h"
#include "game/audio/gameaudio.h"
#include "sead/random.h"
#include "game/movementhandler.h"
const u32 timerThreshold = 315;

class Thundercloud : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(Thundercloud, Enemy);

public:
    Thundercloud(const ActorBuildInfo* buildInfo);
    virtual ~Thundercloud() { }
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

    ModelWrapper* model;
    MovementHandler movementHandler;
    struct {
        PlayerBase* player;
        u32 timer;
    } playerTimers[4];
   Actor* child;
    u16 spawnProfileID;
    
   u32 delay;

    bool spawned;
};

REGISTER_PROFILE(Thundercloud, ProfileID::Thundercloud);
PROFILE_RESOURCES(ProfileID::Thundercloud, Profile::LoadResourcesAt::Course, "tc", "karon");

HitboxCollider::Info Thundercloud::collisionInfo = {
    Vec2f(0.0f, 4.0f), Vec2f(25.0f, 16.0f), HitboxCollider::Shape::Rectangle, 5, 0, 0x824F, 0xFFFBFFFF, 0, &Enemy::collisionCallback
};

Thundercloud::Thundercloud(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
    , model(nullptr)
    , movementHandler()
{ }

u32 Thundercloud::onCreate() {
    this->model = ModelWrapper::create("tc", "tc", 1);
    this->model->playSklAnim("run");
    this->model->loopSklAnims(true);

    this->hitboxCollider.init(this, &Thundercloud::collisionInfo);
    this->addHitboxColliders();
    this->delay = 0;

    for (u32 i = 0; i < 4; i++) {
        this->playerTimers[i].player = PlayerMgr::instance()->players[i];
        this->playerTimers[i].timer = timerThreshold;
    }

    u32 movementMask = this->movementHandler.getMaskForMovementType(this->settings2 & 0xFF);
    this->movementHandler.link(this->position, movementMask, this->movementID);
    
    
    
   
    
    return this->onExecute();
}

u32 Thundercloud::onExecute() {
    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position);
    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateAnimations();
    this->model->updateModel();
    
    for (u32 i = 0; i < 4; i++) {
        if (this->playerTimers[i].timer <= timerThreshold) {
            this->playerTimers[i].timer++;
        }
    }
     
     
     this->delay++;
     if (this->delay >= (this->settings1 >> 0x18) * 0xA ) {
     GameAudio::startSoundMap(SoundEffects::SE_BOSS_KOOPA_LAND, self->position);
     ActorBuildInfo Lightning = { 0 };
     Lightning.profile = Profile::get(668);
     Lightning.position = this->position + Vec3f(0.0f, -8.0f, 0.0f);
     ActorMgr::instance()->create(Lightning, 0);
     this->delay  = 0;
}
    

    this->movementHandler.execute();
    this->position = this->movementHandler.position;
    return 1;
}

u32 Thundercloud::onDraw() {
   this->model->draw();
    
    return 1;
}

void Thundercloud::collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    for (u32 i = 0; i < 4; i++) {
        if (hcOther->owner == this->playerTimers[i].player && this->playerTimers[i].timer >= timerThreshold) {
            this->playerTimers[i].timer = 0;
            static_cast<PlayerBase*>(hcOther->owner)->doDamage(this, PlayerBase::DamageType::Electric);
        }
    }
}

void Thundercloud::collisionYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    this->collisionPlayer(hcSelf, hcOther);;
}


bool Thundercloud::collisionStar(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    Vec3f effectOrigin(this->position.x, this->position.y, 4500.0f);
    Vec3f effectPos(effectOrigin);
    Effect::spawn(RP_Jugemu_CloudDisapp, &effectPos, nullptr, &this->scale);

    this->isDeleted = true;
    return true;
}

bool Thundercloud::collisionFireball(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    hcOther->owner->isDeleted = true;
    return true;
}

bool Thundercloud::collisionIceball(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    hcOther->owner->isDeleted = true;

    return true;
}

bool Thundercloud::collisionGroundPoundYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    this->collisionPlayer(hcSelf, hcOther);

    return true;
}

bool Thundercloud::collisionGroundPound(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    this->collisionPlayer(hcSelf, hcOther);

    return true;
}

bool Thundercloud::collisionPropellerDrill(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    this->collisionPlayer(hcSelf, hcOther);
    return true;
}

bool Thundercloud::collisionSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    this->collisionPlayer(hcSelf, hcOther);

    return true;
}

bool Thundercloud::collisionPenguinSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    this->collisionPlayer(hcSelf, hcOther);

    return true;
}

bool Thundercloud::collisionThrowableObject(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
     hcOther->owner->isDeleted = true;

    return true;
}

bool Thundercloud::collisionFireballYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    hcOther->owner->isDeleted = true;

    return true;
}

