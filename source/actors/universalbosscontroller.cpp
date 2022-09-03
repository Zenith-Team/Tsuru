#include "tsuru/actor/bosswrapper.h"
#include "game/actor/stage/cutscenekamek.h"
#include "game/actor/actormgr.h"
#include "game/profile/profileid.h"
#include "log.h"

class UniversalBossController : public BossControllerWrapper {
public:
    UniversalBossController(const ActorBuildInfo* buildInfo)
        : BossControllerWrapper(buildInfo)
        , firstIteration(true)
    { }

    virtual ~UniversalBossController() { }

    static Actor* build(const ActorBuildInfo* buildInfo) {
        return new UniversalBossController(buildInfo);
    }

    Boss* getTargetBoss() override {
        if (this->firstIteration) {
            this->firstIteration = false;
            return nullptr;
        }

        for (Actor** current = ActorMgr::instance()->actors.start.buffer; current < ActorMgr::instance()->actors.end.buffer; current++) {
            Actor* actor = *current;
            if (actor) {
                if (((StageActor*)actor)->type == StageActor::StageActorType_Boss) {
                    return (Boss*)actor;
                }
            }
        }

        return nullptr;
    }

    void spawnCutsceneKamek() override {
        ActorBuildInfo buildInfo = { 0 };
        buildInfo.profile = Profile::get(ProfileID::CutsceneKamek);

        static_cast<CutsceneKamek*>(ActorMgr::instance()->create(buildInfo, 0))->doStateChange(&CutsceneKamek::StateID_CutsceneKamekState2);
    }

    bool firstIteration;
};

const Profile UniversalBossControllerProfile(&UniversalBossController::build, ProfileID::UniversalBossController);
