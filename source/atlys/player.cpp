#include "tsuru/atlys/player.h"
#include "tsuru/atlys/scene.h"
#include "game/util.h"

CREATE_STATE(Atlys::Player, Idle);
CREATE_STATE(Atlys::Player, Walking);

const Profile AtlysPlayerProfile(&Atlys::Player::build, ProfileID::AtlysPlayer);
PROFILE_RESOURCES(ProfileID::AtlysPlayer, "kanibo");

Atlys::Player::Player(const ActorBuildInfo* buildInfo)
    : Atlys::Actor(buildInfo)
    , states(this)
    , model(nullptr)
    , currentNode(nullptr)
    , targetNode(nullptr)
    , tex()
{ }

Actor* Atlys::Player::build(const ActorBuildInfo* buildInfo) {
    return new Atlys::Player(buildInfo);
}

u32 Atlys::Player::onCreate() {
    this->currentNode = Atlys::Scene::instance()->map->findNodeByID(0);
    this->position = this->currentNode->position;
    this->states.changeState(&Atlys::Player::StateID_Idle);

    return 1;
}

u32 Atlys::Player::onExecute() {
    this->states.execute();

    LOG("Current node: %u", this->currentNode->id);
    if (this->targetNode) {
        LOG("Target node: %u", this->targetNode->id);
    }

    return 1;
}

u32 Atlys::Player::onDraw() {

    return 1;
}

void Atlys::Player::findTargetNode(Direction::DirectionType direction) {
    if (this->currentNode->connections[direction].unlocked && this->currentNode->connections[direction].node != 0xFFFFFFFF) {
        this->targetNode = Atlys::Scene::instance()->map->findNodeByID(this->currentNode->connections[direction].node);
        this->walkingSpeed = this->currentNode->connections[direction].speed;
        this->states.changeState(&Atlys::Player::StateID_Walking);
    } // TODO: Else rotate to direction to match game behavior
}

/* STATE: Idle */

void Atlys::Player::beginState_Idle() { }

void Atlys::Player::executeState_Idle() {
    const InputControllers& controllers = Atlys::Scene::instance()->controllers;

    // TODO: Get the active controller from game
    InputControllers::ControllerID activeController = InputControllers::ControllerID_Gamepad;

    // Find the target node
    if (controllers.buttonRight(activeController))
        this->findTargetNode(Direction::Right);
    else if (controllers.buttonLeft(activeController))
        this->findTargetNode(Direction::Left);
    else if (controllers.buttonUp(activeController))
        this->findTargetNode(Direction::Up);
    else if (controllers.buttonDown(activeController))
        this->findTargetNode(Direction::Down);
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
    }

    LOG("Walking to node at %f, %f, current position: %f, %f", this->targetNode->position.x, this->targetNode->position.y, this->position.x, this->position.y);
    
    bool x = moveFloatTo(this->position.x, this->targetNode->position.x, this->walkingSpeed);
    bool y = moveFloatTo(this->position.y, this->targetNode->position.y, this->walkingSpeed);

    if (x && y)
        this->states.changeState(&Atlys::Player::StateID_Idle);
}

void Atlys::Player::endState_Walking() {
    this->currentNode = this->targetNode;
    this->targetNode = nullptr;
    this->walkingSpeed = 0.0f;
}
