#pragma once

#include "sead/heap.h"
#include "tsuru/custompowerupmodel.h"

struct PlayerAdditionalResource {
    PlayerAdditionalResource();

    CustomPowerupModel customPowerupModel;

    void init_(Player* target);

    static void init(Player* target);

    static PlayerAdditionalResource data[4];
};
