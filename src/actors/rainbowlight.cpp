#include "game/actor/stage/stageactor.h"
#include "game/graphics/lightsource.h"
#include "game/graphics/mask/lightmask.h"
#include "log.h"

class RainbowLight : public StageActor {
    SEAD_RTTI_OVERRIDE(RainbowLight, StageActor);

public:
    RainbowLight(const ActorBuildInfo* buildInfo);
    virtual ~RainbowLight() { }

    u32 onCreate() override;
    u32 onDraw() override;

    LightSource lightSource;
    sead::Color4f lightColor;
    LightMask lightMask;
    f32 lightAttenuationRadius;
};

REGISTER_PROFILE(RainbowLight, ProfileID::RainbowLight);

RainbowLight::RainbowLight(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
{ }

u32 RainbowLight::onCreate() {
    // Nybble 2 squared
    this->lightAttenuationRadius = (this->eventID1 & 0xF) * (this->eventID1 & 0xF) * 1.5f;

    switch (this->eventID1 >> 0x4 & 0xF) { // Nybble 1
        default:
        case 0: this->lightColor = sead::Color4f::cRed;      break;
        //case 1: this->lightColor = sead::colorOrange;   break; // TODO
        case 2: this->lightColor = sead::Color4f::cYellow;   break;
        case 3: this->lightColor = sead::Color4f::cGreen;    break;
        case 4: this->lightColor = sead::Color4f::cCyan;     break;
        case 5: this->lightColor = sead::Color4f::cBlue;     break;
        case 6: this->lightColor = sead::Color4f::cWhite;    break;
    }

    this->lightSource.update(0, &this->position, nullptr, &this->lightAttenuationRadius, nullptr, &this->lightColor);

    this->lightMask.init(nullptr, 2);
    this->lightMask.position = this->position;
    this->lightMask.radius = this->lightAttenuationRadius;
    this->lightMask.update();

    return 1;
}

u32 RainbowLight::onDraw() {
    this->lightSource.update(0, &this->position, nullptr, &this->lightAttenuationRadius, nullptr, &this->lightColor);

    this->lightMask.position = this->position;
    this->lightMask.update();

    this->lightMask.draw();

    return 1;
}
