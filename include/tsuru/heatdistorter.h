#pragma once

#include "game/effect/effect.h"
#include "game/effect/effectid.h"

class HeatDistorter {
public:
    HeatDistorter()
        : effect()
    { }

    ~HeatDistorter() { }

    void execute(const Vec3f& position, const Vec3f& size) {
        const Vec3u rot;
        this->effect.update(RP_Firebar, &position, &rot, &size);
    }

private:
    EffectWrapper effect;
};
