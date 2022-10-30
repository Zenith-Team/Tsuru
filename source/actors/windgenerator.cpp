#include "game/actor/stage/windgenerator.h"
#include "game/playermgr.h"
#include "game/actor/actormgr.h"
#include "log.h"

class FixedWindGenerator : public WindGenerator {
    SEAD_RTTI_OVERRIDE_IMPL(FixedWindGenerator, WindGenerator)

public:
    FixedWindGenerator(const ActorBuildInfo* buildInfo);
    virtual ~FixedWindGenerator() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onExecute() override;
};

const Profile FixedWindGeneratorProfile(&FixedWindGenerator::build, 793);

const u32 affectedActors[] = {
    ProfileID::Goomba,
    ProfileID::Goombrat,
    ProfileID::ParaGoomba,
    ProfileID::KoopaTroopa,
    ProfileID::ParaKoopa,
    ProfileID::BuzzyBeetle,
    ProfileID::SpikeTop,
    ProfileID::Spiny,
    ProfileID::Pokey,
    447, 448, 449 // TODO: Add these to ProfileID
};

FixedWindGenerator::FixedWindGenerator(const ActorBuildInfo* buildInfo)
    : WindGenerator(buildInfo)
{ }

Actor* FixedWindGenerator::build(const ActorBuildInfo* buildInfo) {
    return new FixedWindGenerator(buildInfo);
}

u32 FixedWindGenerator::onExecute() {
    // Blow players
    for (u32 i = 0; i < 4; i++) {
        Player* player = PlayerMgr::instance()->players[i];
        if (player != nullptr) {
            switch (this->eventID1 >> 0x4 & 0xF) {
                case 0: player->position.x += this->finalWindStrength * 2.5; break;
                case 1: player->position.x -= this->finalWindStrength * 2.5; break;
                case 2: player->position.y += this->finalWindStrength * 2.5; break;
                case 3: player->position.y -= this->finalWindStrength * 2.5; break;
            }
        }
    }

    // Blow actors
    for (Actor** current = ActorMgr::instance()->actors.start.buffer; current < ActorMgr::instance()->actors.end.buffer; current++) {
        Actor* actor = *current;
        if (actor != nullptr) {
            u32 profileID = actor->getProfileID();
            for (u32 i = 0; i < sizeof(affectedActors) / sizeof(u32); i++) {
                if (profileID == affectedActors[i]) {
                    switch (this->eventID1 >> 0x4 & 0xF) {
                        case 0: ((StageActor*)actor)->position.x += this->finalWindStrength * 2.5; break;
                        case 1: ((StageActor*)actor)->position.x -= this->finalWindStrength * 2.5; break;
                        case 2: ((StageActor*)actor)->position.y += this->finalWindStrength * 2.5; break;
                        case 3: ((StageActor*)actor)->position.y -= this->finalWindStrength * 2.5; break;
                    }

                    break;
                }
            }
        }
    }

    return 1;
}
