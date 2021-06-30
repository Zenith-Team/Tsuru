#include "actor/brosbase.h"

#include "drawmgr.h"
#include "actormgr.h"

class BombBro : public BrosBase {
public:
    BombBro(const ActorBuildInfo* buildInfo);
    virtual ~BombBro() { }

    static BaseActor* build(const ActorBuildInfo* buildInfo);

    void throwProjectile() override;

    void spawnProjectile();
};

const ActorInfo BombBroActorInfo = { Vec2i(8, -16), Vec2i(0, 16), Vec2i(8, 16), 0, 0, 0, 0, 32 };
const Profile BombBroProfile(&BombBro::build, ProfileId::Sprite572, "BombBro", &BombBroActorInfo, 0x12);
PROFILE_RESOURCES(ProfileId::Sprite572, "star_coin");

BombBro::BombBro(const ActorBuildInfo* buildInfo) : BrosBase(buildInfo) { }

BaseActor* BombBro::build(const ActorBuildInfo* buildInfo) {
    return new BombBro(buildInfo);
}

void BombBro::throwProjectile() {
    ActorBuildInfo buildInfo = { 0 };
    buildInfo.profile = Profile::get(ProfileId::Sprite0);
    buildInfo.position = position;
    buildInfo.parentId = id;

    Enemy* projectile;

    projectile = reinterpret_cast<Enemy*>(ActorMgr::instance->create(&buildInfo, 0));
    projectile->speed.x = 4.0f;
}

