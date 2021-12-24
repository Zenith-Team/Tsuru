#include "tsuru/atlys/node.h"
#include "game/graphics/drawmgr.h"
#include "game/resource/resmgr.h"

const Profile AtlysNodeProfile(&Atlys::Node::build, ProfileID::AtlysNode, "AtlysNode", nullptr, 0, Profile::LoadResourcesAt_Boot);
static const u32 profileResourceCount6 = 1;
typedef int static_assert_6[(profileResourceCount6 <= 0xFF) ? 1 : -1];
static const sead::SafeString profileResourceFiles6[] = { "kanibo" };
static const ProfileResources profileResources6(ProfileID::AtlysNode, profileResourceCount6, profileResourceFiles6);

Atlys::Node::Node(const ActorBuildInfo* buildInfo)
    : Actor(buildInfo)
    , color(NodeColor_Red)
{
    this->position = buildInfo->position;
    this->rotation = buildInfo->rotation;
}

Actor* Atlys::Node::build(const ActorBuildInfo* buildInfo) {
    return new Atlys::Node(buildInfo);
}

u32 Atlys::Node::onCreate() {
    //this->model = ModelWrapper::create(ResArchiveMgr::instance()->get("MarioMdl"), "PMB_model");

    this->model = ModelWrapper::create("kanibo", "kanibo");

    return 1;
}

u32 Atlys::Node::onDraw() {
    this->updateModel();
    DrawMgr::instance()->drawModel(this->model);

    return 1;
}
