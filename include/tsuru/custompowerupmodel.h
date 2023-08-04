#pragma once

#include "game/graphics/model/charactermodelmgr.h"

class Player;

class CustomPowerupModel {
public:
    CustomPowerupModel();
    ~CustomPowerupModel();

    void init_(Player* target);
    void draw_(Player* target);

    static void init(Player* target);
    static void draw(Player* target);

    s32 headBoneID, rootBoneID;

    // Hammer Suit
    ModelWrapper* hammerHelmet;
    ModelWrapper* hammerShell;
};
