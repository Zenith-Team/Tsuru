#include "actor/actor.h"

#include "model.h"


class WavePlaftorm : public Actor {
public:
    WavePlaftorm(const ActorBuildInfo* buildInfo);
    virtual ~WavePlaftorm() { }

    static BaseActor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    bool updateWaveTargets();

    ModelWrapper* model;
    
    f32 targetPos;
    u32 targetRot;

    bool isOffScreen;

    u8 width;
};

const Profile WavePlaftormProfile(&WavePlaftorm::build, ProfileId::Sprite521, "WavePlaftorm", nullptr, 0);
PROFILE_RESOURCES(ProfileId::Sprite521, "lift_han_wood"); // TODO: figure out if you can add multiple archives here

WavePlaftorm::WavePlaftorm(const ActorBuildInfo* buildInfo) : Actor(buildInfo) { }

BaseActor* WavePlaftorm::build(const ActorBuildInfo* buildInfo) {
    return new WavePlaftorm(buildInfo);
}

u32 WavePlaftorm::onCreate() {
    model = ModelWrapper::create("star_coin", "star_coinA");

    isOffScreen = true;
    onExecute();

    return 1;
}
