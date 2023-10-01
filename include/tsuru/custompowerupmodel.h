#pragma once

#include "game/graphics/model/charactermodelmgr.h"

class Player;

class CustomPowerupModel {
public:
    CustomPowerupModel();
    ~CustomPowerupModel();

    void init_();
    void draw_(PlayerModel* playerModel);

    static void draw(s8 playerID, PlayerModel* playerModel);

    // Hammer Suit
    ModelWrapper* hammerHelmet;
    ModelWrapper* hammerShell;
};
