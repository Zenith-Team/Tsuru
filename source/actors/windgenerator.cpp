#include <game/actor/stage/windgenerator.h>
#include <game/playermgr.h>
#include <game/actor/actormgr.h>
#include <log.h>

class FixedWindGenerator : public WindGenerator {
public:
    FixedWindGenerator(const ActorBuildInfo* buildInfo);
    virtual ~FixedWindGenerator() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onExecute() override;
};

const Profile FixedWindGeneratorProfile(&FixedWindGenerator::build, 793, "FixedWindGenerator", nullptr, 0);

const u32 affectedActors[] = {
    467, 469, 512, 515, 381, 676, 517, 505, 447, 448, 449
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
        Player* player = PlayerMgr::sInstance->mPlayers[i];
        if (player)
            player->mPosition.x += this->mFinalWindStrength * 2.5;
    }

    // Blow actors
    Actor** current = ActorMgr::sInstance->mActors.mBuffer.mBuffer;
    while (current < ActorMgr::sInstance->mActors.mLast) {
        Actor* actor = *current;
        if (actor) {
            u32 profileID = actor->getProfileID();
            for (u32 i = 0; i < 10; i++) {
                if (profileID == affectedActors[i]) {
                    ((StageActor*)actor)->mPosition.x += this->mFinalWindStrength * 2.5;
                    break;
                }
            }
        }

        current++;
    }

    LOG("wind state: %i", this->_298);

    return 1;
}
