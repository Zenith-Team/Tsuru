#pragma once

#include <game/graphics/model/charactermodel.h>

class YoshiModel;

class CharacterModelMgr {
public:
    CharacterModelMgr();

    virtual void vfC(); // nullsub

    void draw();

    void* _0;
    u32 _4;
};

class YoshiModelMgr : public CharacterModelMgr {
public:
    // @param color The color of the Yoshi model
    YoshiModelMgr(YoshiModel::TexColor color);

    YoshiModel* yoshiModel;
};
