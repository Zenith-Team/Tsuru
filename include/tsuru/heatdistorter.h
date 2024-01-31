#pragma once

#include "game/effect/effect.h"
#include "game/effect/effectid.h"

class HeatDistorter {
public:
    HeatDistorter()
        : effect()
    { }

    ~HeatDistorter() { }

    void execute(const sead::Vector3f& position, const sead::Vector3f& size) {
        const sead::Vector3u rot;
        this->effect.update(RP_Firebar, &position, &rot, &size);
    }

private:
    EffectWrapper effect;
};
