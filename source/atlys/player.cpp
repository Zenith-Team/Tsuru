#include "tsuru/atlys/player.h"
#include "tsuru/atlys/scene.h"
#include "math/functions.h"
#include "sead/mathcalccommon.h"
#include "game/task/taskmgr.h"
#include "game/level/levelinfo.h"
#include "game/task/coursetask.h"
#include "game/resource/resmgr.h"
#include "log.h"

CREATE_STATE(Atlys::Player, Idle);
CREATE_STATE(Atlys::Player, Walking);

const Profile AtlysPlayerProfile(&Atlys::Player::build, ProfileID::AtlysPlayer);

Atlys::Player::Player(const ActorBuildInfo* buildInfo)
    : Atlys::Actor(buildInfo)
    , states(this)
    , model(nullptr)
    , currentNode(nullptr)
    , targetNode(nullptr)
    , walkingSpeed(0.0f)
    , targetRotation(0)
    , direction(Direction::Right)
{ }

Atlys::Player::~Player() {
    if (this->model)
        delete this->model;

    this->model = nullptr;
}

Actor* Atlys::Player::build(const ActorBuildInfo* buildInfo) {
    return new Atlys::Player(buildInfo);
}

u32 Atlys::Player::onCreate() {
    this->model = ModelWrapper::create(ResArchiveMgr::instance()->get("MarioMdl"), "MB_model");

    this->currentNode = Atlys::Scene::instance()->map->findNodeByID(0);
    this->position = this->currentNode->position;
    this->states.changeState(&Atlys::Player::StateID_Idle);

    return 1;
}

u32 Atlys::Player::onExecute() {
    this->states.execute();

    if (this->rotation.y != this->targetRotation)
        sead::Mathu::chase(&this->rotation.y, this->targetRotation, 0x9000000);

    return 1;
}

u32 Atlys::Player::onDraw() {
    DrawMgr::instance()->drawModel(this->updateModel());

    return 1;
}

void Atlys::Player::updateTargetRotation() {
    this->targetRotation = 0x40000000 - // 90 degrees
    fixDeg(radToDeg(atan2f(
        this->targetNode->position.y - this->position.y,
        this->targetNode->position.x - this->position.x
    )));
}

ModelWrapper* Atlys::Player::updateModel() {
    Mtx34 mtx;
    mtx.makeIdentity();
    mtx.rotateAndTranslate(this->rotation, Vec3f(this->position.x, 0.0f, this->position.y));
    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateModel();

    return this->model;
}

void Atlys::Player::findTargetNode(Direction::DirectionType direction) {
    Map::Node* target = nullptr;

    if (this->currentNode->type == Map::Node::Type_Normal && this->currentNode->Normal_connections[direction].node != ATLYS_NODE_INVALID)
        target = Atlys::Scene::instance()->map->findNodeByID(this->currentNode->Normal_connections[direction].node);
    else if (this->currentNode->type == Map::Node::Type_Level && this->currentNode->Level_connections[direction].node != ATLYS_NODE_INVALID)
        target = Atlys::Scene::instance()->map->findNodeByID(this->currentNode->Level_connections[direction].node);

    if (!target)
        return;

    if (this->currentNode->type == Map::Node::Type_Normal && this->currentNode->Normal_connections[direction].node != ATLYS_NODE_INVALID)
        this->walkingSpeed = this->currentNode->Normal_connections[direction].speed;
    else if (this->currentNode->type == Map::Node::Type_Level && this->currentNode->Level_connections[direction].node != ATLYS_NODE_INVALID)
        this->walkingSpeed = this->currentNode->Level_connections[direction].speed;

    this->direction = direction;
    this->targetNode = target;
    this->states.changeState(&Atlys::Player::StateID_Walking);
    this->updateTargetRotation();
}

/* STATE: Idle */

void Atlys::Player::beginState_Idle() { }

void Atlys::Player::executeState_Idle() {
    const InputControllers* controllers = &Atlys::Scene::instance()->controllers;

    if (controllers->buttonA(Atlys::Scene::instance()->activeController) && this->currentNode->type == Map::Node::Type_Level)
       TaskMgr::instance()->startLevel(Atlys::Scene::instance(), this->currentNode->world, this->currentNode->level);

    // Find the target node
    for (u32 i = 0; i < 4; i++) {
        if (controllers->DPadDirection(i, Atlys::Scene::instance()->activeController)) {
            this->findTargetNode((Direction::DirectionType) i);
            if (!this->targetNode) {
                switch (i) {
                    // TODO: Do this without a switch
                    case Direction::Up: this->targetRotation = fixDeg(180.0f); break;
                    case Direction::Down: this->targetRotation = fixDeg(0.0f); break;
                    case Direction::Left: this->targetRotation = fixDeg(270.0f); break;
                    case Direction::Right: this->targetRotation = fixDeg(90.0f); break;
                }
            }

            break;
        };
    }
}

void Atlys::Player::endState_Idle() { }

/* STATE: Walking */

void Atlys::Player::beginState_Walking() {
    if (!this->targetNode) {
        LOG("Walk to target node failed because nullptr");
        this->states.changeState(&Atlys::Player::StateID_Idle);
    }
}

void Atlys::Player::executeState_Walking() {
    if (!this->targetNode) {
        LOG("Walk to target node failed because nullptr");
        this->states.changeState(&Atlys::Player::StateID_Idle);
        return;
    }

    // Pythagorean theorem
    f32 distance = sqrtf(powf(this->targetNode->position.x - this->position.x, 2) + powf(this->targetNode->position.y - this->position.y, 2));
    f32 fullDistance = sqrtf(powf(this->targetNode->position.x - this->currentNode->position.x, 2) + powf(this->targetNode->position.y - this->currentNode->position.y, 2));

    if (distance > this->walkingSpeed) { // Not at the target node yet, move towards it
        // TODO: Use normalized vector instead
        this->position.x += (this->targetNode->position.x - this->position.x) / distance * this->walkingSpeed;
        this->position.y += (this->targetNode->position.y - this->position.y) / distance * this->walkingSpeed;

        // We are 66% to target, do we want to go back?
        if (distance < (fullDistance / 3.0f)) {
            const InputControllers* controllers = &Atlys::Scene::instance()->controllers;

            for (u32 i = 0; i < 4; i++) {
                if (Direction::opposite(this->direction) == i && controllers->DPadDirection(i, Atlys::Scene::instance()->activeController)) {
                    // Swap target/current node
                    swap(this->targetNode, this->currentNode);

                    // Swap direction
                    this->direction = Direction::opposite(this->direction);

                    this->updateTargetRotation();

                    break;
                };
            }
        }
    } else { // Reached target
        this->position = this->targetNode->position;

        switch (this->targetNode->type) {
            case Map::Node::Type_Passthrough: {
                // If we reached the target and the type is passthrough, instead of stopping change target to the next node
                this->targetNode = Atlys::Scene::instance()->map->findNodeByID(this->targetNode->Passthrough_connections[this->targetNode->Passthrough_connections[0].node == this->currentNode->id].node);

                // Set current node to the passthrough we are on so that returning will work properly
                this->currentNode = this->targetNode;

                this->updateTargetRotation();
                break;
            }

            case Map::Node::Type_Transition: {
                // If we reached the target and the type is transition, teleport to the target node

                // TODO: Wait for transition to finish

                this->targetNode = Atlys::Scene::instance()->map->findNodeByID(this->targetNode->targetNodeID);
                this->states.changeState(&Atlys::Player::StateID_Idle);
                break;
            }

            default: {
                this->states.changeState(&Atlys::Player::StateID_Idle);
                break;
            }
        }
    }
}

void Atlys::Player::endState_Walking() {
    this->currentNode = this->targetNode;
    this->position = this->currentNode->position;
    this->targetNode = nullptr;
    this->walkingSpeed = 0.0f;
}
