#include "game/actor/stage/multistateactor.h"
#include "game/graphics/model/modelnw.h"
#include "game/actor/stage/playerbase.h"
#include "game/playermgr.h"
#include "game/level/level.h"
#include "game/level/levelinfo.h"
#include "log.h"

class Minecart : public MultiStateActor {
    SEAD_RTTI_OVERRIDE(Minecart, MultiStateActor);

public:
    Minecart(const ActorBuildInfo* buildInfo);
    virtual ~Minecart() { }

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    ModelWrapper* model;
    PlayerBase* player;
    Level::Area::PathNode* path;
    u16 nodeCount;
    u16 currentNode;

    DECLARE_STATE(Minecart, Idle);
    DECLARE_STATE(Minecart, Ride);
};

CREATE_STATE(Minecart, Idle);
CREATE_STATE(Minecart, Ride);

REGISTER_PROFILE(Minecart, ProfileID::Minecart);
PROFILE_RESOURCES(ProfileID::Minecart, Profile::LoadResourcesAt::Course, "truck");

Minecart::Minecart(const ActorBuildInfo* buildInfo)
    : MultiStateActor(buildInfo)
    , model(nullptr)
    , player(nullptr)
{ }

u32 Minecart::onCreate() {
    this->model = ModelWrapper::create("truck", "truck", 4);

    this->scale = sead::Vector3f(0.2f, 0.2f, 0.2f);
    this->position.y -= 16.0f;
    this->position.z = 4500.0f;
    this->rotation.y = sead::Mathf::deg2idx(90.0f);
    this->model->playSklAnim("Wait");

    Level::Area* const area = Level::instance()->getArea(LevelInfo::instance()->area);

    this->path = area->getPathNodes(this->eventID1 >> 0x4 & 0xF);            // nybble 1
    this->nodeCount = area->getPath(this->eventID1 >> 0x4 & 0xF)->nodeCount; // nybble 1
    this->currentNode = 0;

    this->player = PlayerMgr::instance()->players[0];

    this->doStateChange(&Minecart::StateID_Ride);

    return this->onExecute();
}

u32 Minecart::onExecute() {
    this->states.execute();

    sead::Matrix34f mtx;
    mtx.makeRTIdx(this->rotation, this->position + sead::Vector3f(0.0f, 21.0f, 0.0f));

    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateModel();
    this->model->updateAnimations();

    return 1;
}

u32 Minecart::onDraw() {
    this->model->draw();

    return 1;
}

/** STATE: Idle */

void Minecart::beginState_Idle() { }
void Minecart::executeState_Idle() { }
void Minecart::endState_Idle() { }

/** STATE: Ride */

void Minecart::beginState_Ride() { }

void Minecart::executeState_Ride() {
    if (this->currentNode >= this->nodeCount) {
        return;
    }

    sead::Vector3f target(this->path[this->currentNode].x, -(this->path[this->currentNode].y + 16.0f), this->position.z);

    sead::Vector3f diff = target - this->position;
    diff.normalize();
    this->position += diff * this->path[this->currentNode].speed;

    sead::Mathu::chase(&this->rotation.z, sead::Mathf::rad2idx(atan2f(target.y - this->position.y, target.x - this->position.x)), sead::Mathf::deg2idx(3.0f));

    if (position.squaredDistance(target) < sead::Mathf::square(2.0f)) {
        this->currentNode++;
    }

    this->player->position = this->position + sead::Vector3f(0.0f, 24.0f, 0.0f);
}

void Minecart::endState_Ride() { }
