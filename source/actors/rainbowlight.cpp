#include "game/actor/stage/stageactor.h"
#include "game/graphics/lightsource.h"
#include "game/graphics/mask/lightmask.h"
#include "log.h"

class RainbowLight : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(RainbowLight, StageActor)

public:
    RainbowLight(const ActorBuildInfo* buildInfo);
    virtual ~RainbowLight() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    LightSource lightSource;
    sead::Color4f lightColor;
    LightMask lightMask;
    f32 lightAttenuationRadius;
};

const ActorInfo RainbowLightActorInfo = {
    Vec2i(0, 0), Vec2i(0, 0), Vec2i(240, 240), 0, 0, 0, 0, 0
};

const Profile RainbowLightProfile(&RainbowLight::build, ProfileID::RainbowLight, "RainbowLight", nullptr, 0);

RainbowLight::RainbowLight(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
{ }

Actor* RainbowLight::build(const ActorBuildInfo* buildInfo) {
    return new RainbowLight(buildInfo);
}

u32 RainbowLight::onCreate() {
    // Nybble 2 squared
    this->lightAttenuationRadius = (this->eventID1 & 0xF) * (this->eventID1 & 0xF) * 1.5f;

    switch (this->eventID1 >> 0x4 & 0xF) { // Nybble 1
        case 0: this->lightColor = sead::colorRed;      break;
        case 1: this->lightColor = sead::colorOrange;   break;
        case 2: this->lightColor = sead::colorYellow;   break;
        case 3: this->lightColor = sead::colorGreen;    break;
        case 4: this->lightColor = sead::colorCyan;     break;
        case 5: this->lightColor = sead::colorBlue;     break;
        case 6: this->lightColor = sead::colorWhite;    break;
        default: this->lightColor = sead::colorRed;     break;
    }

    this->lightSource.update(0, &this->position, nullptr, &this->lightAttenuationRadius, nullptr, &this->lightColor);

    this->lightMask.init(nullptr, 2);
    this->lightMask.position = this->position;
    this->lightMask.radius = this->lightAttenuationRadius;
    this->lightMask.update();

    return 1;
}

u32 RainbowLight::onExecute() {
    // TODO: Movement controller setup

    this->lightSource.update(0, &this->position, nullptr, &this->lightAttenuationRadius, nullptr, &this->lightColor);

    this->lightMask.position = this->position;
    this->lightMask.update();

    return 1;
}

u32 RainbowLight::onDraw() {
    this->lightMask.draw();

    return 1;
}
