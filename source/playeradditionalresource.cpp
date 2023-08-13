#include "tsuru/playeradditionalresource.h"
#include "game/actor/stage/player.h"

PlayerAdditionalResource PlayerAdditionalResource::data[4];

PlayerAdditionalResource::PlayerAdditionalResource()
    : customPowerupModel()
{ }

void PlayerAdditionalResource::init_(Player* target) {
    this->customPowerupModel.init_(target);
}

void PlayerAdditionalResource::init(Player* target) {
    PlayerAdditionalResource::data[target->playerID].init_(target);
}

ASM_BEGIN

.include "macros.S"

.global InitPlayerAdditionalResource
InitPlayerAdditionalResource:
    mr r3, r31
    SafeBranch init__24PlayerAdditionalResourceSFP6Player
    blr

ASM_END
