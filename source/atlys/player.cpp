#include "tsuru/atlys/player.h"
#include "tsuru/atlys/scene.h"

const Profile AtlysPlayerProfile(&Atlys::Player::build, ProfileID::AtlysPlayer);
PROFILE_RESOURCES(ProfileID::AtlysPlayer, "kanibo");

Atlys::Player::Player(const ActorBuildInfo* buildInfo)
    : Atlys::Actor(buildInfo)
    , states(this)
    , model(nullptr)
    , tex()
{ }

Actor* Atlys::Player::build(const ActorBuildInfo* buildInfo) {
    return new Atlys::Player(buildInfo);
}

u32 Atlys::Player::onCreate() {
    this->position = Atlys::Scene::instance()->map->findNodeByID(0)->position;

    return 1;
}

u32 Atlys::Player::onExecute() {

    return 1;
}

u32 Atlys::Player::onDraw() {

    return 1;
}
