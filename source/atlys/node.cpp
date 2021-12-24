#include "tsuru/atlys/node.h"
#include "game/graphics/drawmgr.h"

const Profile AtlysNodeProfile(&Atlys::Node::build, ProfileID::AtlysNode);

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
    this->model = ModelWrapper::create(ResArchiveMgr::instance()->get("MarioMdl"), "PMB_model");

    return 1;
}

u32 Atlys::Node::onDraw() {
    this->updateModel();
    DrawMgr::instance()->drawModel(this->model);

    return 1;
}
