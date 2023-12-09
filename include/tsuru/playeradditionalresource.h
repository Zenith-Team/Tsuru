#pragma once

#include "sead/heap.h"
#include "tsuru/custompowerupmodel.h"

struct PlayerAdditionalResource {
    PlayerAdditionalResource();

    CustomPowerupModel customPowerupModel;

    void init_();

    static void init(s8 playerID);

    static PlayerAdditionalResource data[4];
};
