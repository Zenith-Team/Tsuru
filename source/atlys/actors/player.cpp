#include "tsuru/atlys.h"
#include "log.h"
#include "math/functions.h"

CREATE_STATE(Atlys::Player, Idle);
CREATE_STATE(Atlys::Player, Walking);

Atlys::Player::Player(const ActorBuildInfo* buildInfo)
    : Atlys::Actor(buildInfo)
    , states(this)
    , model(nullptr)
{ }

Actor* Atlys::Player::build(const ActorBuildInfo* buildInfo) {
    return new Player(buildInfo);
}

const Profile AtlysPlayerProfile(&Atlys::Player::build, ProfileID::AtlysPlayer);
PROFILE_RESOURCES(ProfileID::AtlysPlayer, "bubble");

u32 Atlys::Player::onCreate() {
    this->states.changeState(&Atlys::Player::StateID_Idle);

    //this->model = ModelWrapper::create("bubble", "bubble");

    return 1;
}

u32 Atlys::Player::onExecute() {
    this->states.execute();

    return 1;
}

void Atlys::Player::updateControllerInput(const InputControllers& controllers) {
    if (controllers.buttonUp(InputControllers::ControllerID_Gamepad) && this->states.currentState() != &Atlys::Player::StateID_Walking) {
        this->states.changeState(&Atlys::Player::StateID_Walking);
    }
}

/* STATE: Idle */

void Atlys::Player::beginState_Idle() { LOG("Starting idle"); }
void Atlys::Player::executeState_Idle() { LOG("Idle"); }
void Atlys::Player::endState_Idle() { LOG("Ending idle"); }

/* STATE: Walking */

void Atlys::Player::beginState_Walking() { 
    LOG("Starting walk");

    // Dummy target
}
void Atlys::Player::executeState_Walking() { LOG("Walking"); }
void Atlys::Player::endState_Walking() { LOG("Ending walk"); }
