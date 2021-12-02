#include <game/actor/actor.h>
#include <game/playermgr.h>
#include <game/actor/stage/player.h>
#include <log.h>

class DebugActor : public Actor {
public:
    DebugActor(const ActorBuildInfo* buildInfo);
    virtual ~DebugActor() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onExecute() override;
};

const Profile DebugActorProfile(&DebugActor::build, ProfileID::DebugActor);

DebugActor::DebugActor(const ActorBuildInfo* buildInfo)
    : Actor(buildInfo)
{ }

Actor* DebugActor::build(const ActorBuildInfo* buildInfo) {
    return new DebugActor(buildInfo);
}

u32 DebugActor::onExecute() {
    if (this->settings1 >> 0x8 & 0xF) { // Nybble 10, Log player inputs
        LOG("----Player Inputs----");
        for (u32 i = 0; i < 4; i++) {
            Player* player = PlayerMgr::instance()->players[i];
            if (player) {
                PlayerInput& input = player->input;

                char data[33];

                for (u32 j = 0; j < 32; j++) {
                    if (input.buttons.bits & 1 << (31 - j))
                        data[j] = '1';
                    else
                        data[j] = '0';
                }

                data[32] = 0;

                LOG("Input data player %i: %s", i, data);
                LOG("Player %i up: %u", i, input.getButtonUp());
                LOG("Player %i down: %u", i, input.getButtonDown());
                LOG("Player %i left: %u", i, input.getButtonLeft());
                LOG("Player %i right: %u", i, input.getButtonRight());
                LOG("Player %i dash: %u", i, input.getButtonDash());
                LOG("Player %i jump: %u", i, input.getButtonJump());
            }
        }
    }

    return 1;
}
