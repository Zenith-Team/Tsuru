#pragma once

#include "game/graphics/model/charactermodel.h"

class YoshiModel;

class CharacterModelMgr {
public:
    CharacterModelMgr();

    virtual void vfC(); // nullsub

    void draw();

    CharacterModel* modelPtr;
    u32 _4;
};

class YoshiModelMgr : public CharacterModelMgr {
public:
    // @param color The color of the Yoshi model
    YoshiModelMgr(YoshiModel::TexColor::__type__ color);

    YoshiModel* yoshiModel;
};

class PlayerModelMgr : public CharacterModelMgr { // Size: 0x10
public:
    PlayerModelMgr(u32 character, u32, u32, bool useLightMaps);

    PlayerModel* playerModel;
};

static_assert(sizeof(PlayerModelMgr) == 0x10, "PlayerModelMgr size mismatch");
