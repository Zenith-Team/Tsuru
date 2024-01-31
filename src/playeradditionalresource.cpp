#include "tsuru/playeradditionalresource.h"
#include "game/actor/stage/player.h"

PlayerAdditionalResource PlayerAdditionalResource::data[4];

PlayerAdditionalResource::PlayerAdditionalResource()
    : customPowerupModel()
{ }

void PlayerAdditionalResource::init_() {
    this->customPowerupModel.init_();
}

void PlayerAdditionalResource::init(s8 playerID) {
    PlayerAdditionalResource::data[playerID].init_();
}

ASM_BEGIN

.include "macros.S"

.global InitPlayerAdditionalResource
InitPlayerAdditionalResource:
    mr r3, r31 // Replaced instruction

    SaveVolatileRegisters // This block is: PlayerAdditionalResource::init(r3->playerID)
    lbz r3, 0x54(r3)
    bl init__24PlayerAdditionalResourceSFSc
    RestoreVolatileRegisters
    blr

.global InitPlayerAdditionalResourceCS
InitPlayerAdditionalResourceCS:
    stfs f0, 0xD4(r31) // Replaced instruction

    SaveVolatileRegisters // This block is: PlayerAdditionalResource::init(0)
    li r3, 0
    bl init__24PlayerAdditionalResourceSFSc
    RestoreVolatileRegisters

    blr

ASM_END
