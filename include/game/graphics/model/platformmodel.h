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

    void init();
    void update(Vec3f& pos, f32 width);
    void draw();

    inline void create(u32 type, u32 width) {
        Vec3i nv3i(0);
        Vec3f nv3f(0);

        this->type = type;
        this->width = width;
        this->rotation = nv3i;
        this->_A0 = nv3f;
        this->init();
    }

    ResArchive* archive;
    ModelWrapper* models[3];
    ModelWrapper* models2[30];
    Vec3f position;
    Vec3f _94;
    Vec3f _A0;
    Vec3f _AC;
    Vec3f _B8;
    Vec3i rotation;
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
