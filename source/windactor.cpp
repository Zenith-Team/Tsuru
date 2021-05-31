#include "actor/windgeneratorbase.h"

#include "input.h"
#include "sound.h"
#include "effect.h"
#include "actormgr.h"
#include "actornames.h"
#include "playermgr.h"


class WindGenerator : public WindGeneratorBase {
public:
    inline WindGenerator(const ActorBuildInfo* buildInfo);
    virtual ~WindGenerator() { }

    static BaseActor* build(const ActorBuildInfo* buildInfo);

    EffectWrapper windEffect;

    u32 onCreate() override;
    u32 onExecute() override;

    void updateEffects();
};

const Profile WindGeneratorProfile(&WindGenerator::build, ProfileId::Sprite197, "WindGenerator", nullptr, 0);
PROFILE_RESOURCES(ProfileId::Sprite197, "env_snow");

inline WindGenerator::WindGenerator(const ActorBuildInfo* buildInfo) : WindGeneratorBase(buildInfo) { }

BaseActor* WindGenerator::build(const ActorBuildInfo* buildInfo) {
    return new WindGenerator(buildInfo);
}

// Affected actors
ActorNames WindGenerators[] = {
	GOOMBA, PARAGOOMBA,
	KOOPA_TROOPA, KOOPA_PARATROOPA,
	BUZZY_BEETLE, SPIKE_TOP, SPINY, POKEY,
	BUBBLE_BABY_YOSHI, BALLOON_BABY_YOSHI, GLOW_BABY_YOSHI
};

u32 WindGenerator::onCreate() {
    WindGeneratorBase::onCreate();

    return 1;
}

u32 WindGenerator::onExecute() {
    if (settings2 & 1) {
        u32 blarg = 0;
        s32 tilt = 25;//InputMgr::instance->controllers[0].getTilt(&blarg, 0.5);

        finalWindStrength = (float)tilt * windStrengthValue / 0x20000000;

        if (finalWindStrength > 0.5 * windStrengthValue || finalWindStrength < -0.5 * windStrengthValue) {
            updateEffects();
        }
    }
    else {
        WindGeneratorBase::onExecute();
        if (windState == 0 || windState == 1) {
            updateEffects();
        }
    }

    if (!(settings2 & 2)) {
        for (u32 i = 0; i < 4; i++) {
            Player* player = PlayerMgr::instance->players[i];
            if (player) {
                player->position.x += finalWindStrength * 2.5;
            }
        }

        Actor** current = ActorMgr::instance->actorList.first;
        while (current < ActorMgr::instance->actorList.last) {
            BaseActor* BaseActor = *current;
            if (BaseActor) {
                ProfileId::ProfileIdType profileId = BaseActor->getProfileId();
                for (u32 i = 0; i < 13; i++) {
                    if (WindGenerators[i] == profileId) {
                        ((Actor*)BaseActor)->position.x += finalWindStrength * 2.5;
                        break;
                    }
                }
            }
            current++;
        }
    }

    return 1;
}

void WindGenerator::updateEffects() {
    PlaySound("SE_AMB_RP_BIG_WINDY", 1);

    Vec3 pos(0, 0, 0);
    Vec3 scale(1, 1, 1);

    if (finalWindStrength > 0) {
        pos.x = 1024;
        scale.x = -1;
    }

    windEffect.update(RP_UI_BoostLine_loop, &pos, 0, &scale);
}
