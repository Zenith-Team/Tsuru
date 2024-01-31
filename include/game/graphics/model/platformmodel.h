#pragma once

#include "game/graphics/model/modelnw.h"

class PlatformModel {
public:
    ENUM_CLASS(Type,
        Wood,
        Stone,
        PinkMushroom,
        BoltPlatform,
        KoopaLift, // boss_koopa_lift, crashes
        Bowser,
        YellowMushroom,
        WoodSnow,
        Sky,
        Tower,
        Karansha
    );

public:
    inline PlatformModel() {
        this->scale = 1.0f;
    }

    /**
     * NOTE: The width must be a multiple of 16, or else the segments will clip into each other
    */

    void init();
    void update(sead::Vector3f& pos, f32 width);
    void draw();

    inline void create(u32 type, u32 width) {
        this->type = type;
        this->width = width;
        this->rotation = sead::Vector3u::zero;
        this->_A0 = sead::Vector3f::zero;
        this->init();
    }

    ResArchive* archive;
    ModelWrapper* models[3];
    ModelWrapper* models2[30];
    sead::Vector3f position;
    sead::Vector3f _94;
    sead::Vector3f _A0;
    sead::Vector3f _AC;
    sead::Vector3f _B8;
    sead::Vector3u rotation;
    f32 fwidth;
    f32 fwidth2;
    f32 _D8;
    u32 width;
    u32 type;
    f32 scale;
    u8 _E8;
    u8 _E9;
    u8 _EA;
    u8 _EB;
};
