#include "game/actor/actor.h"
#include "game/playermgr.h"
#include "game/actor/stage/player.h"
#include "tsuru/log.h"

class DebugActor : public Actor {
    SEAD_RTTI_OVERRIDE(DebugActor, Actor);

public:
    DebugActor(const ActorBuildInfo* buildInfo);
    virtual ~DebugActor() { }

    u32 onExecute() override;
};

REGISTER_PROFILE(DebugActor, ProfileID::DebugActor);

DebugActor::DebugActor(const ActorBuildInfo* buildInfo)
    : Actor(buildInfo)
{ }

u32 DebugActor::onExecute() {
    if (this->settings1 >> 0x8 & 0xF) { // Nybble 10, Log player inputs
        PRINT("----Player Inputs----");
        for (u32 i = 0; i < 4; i++) {
            Player* player = PlayerMgr::instance()->players[i];
            if (player) {
                PlayerInput& input = player->input;

                char data[33];

                for (u32 j = 0; j < 32; j++) {
                    if (input.buttons.isOnBit(31 - j))
                        data[j] = '1';
                    else
                        data[j] = '0';
                }

                data[32] = 0;

                PRINT("Input data player ", i, ": ", data);
                PRINT("Player ", i, " up: ", input.getButtonUp());
                PRINT("Player ", i, " down: ", input.getButtonDown());
                PRINT("Player ", i, " left: ", input.getButtonLeft());
                PRINT("Player ", i, " right: ", input.getButtonRight());
                PRINT("Player ", i, " dash: ", input.getButtonDash());
                PRINT("Player ", i, " jump: ", input.getButtonJump());
            }
        }
    }

    return 1;
}
