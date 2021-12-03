#pragma once

#include <game/graphics/model/model.h>

class PlatformModel {
public:
    enum PlatformType {
	    PlatformType_Wood           = 0,
	    PlatformType_Stone          = 1,
	    PlatformType_PinkMushroom   = 2,
	    PlatformType_BoltPlatform   = 3,
	    PlatformType_Crashes        = 4, // boss_koopa_lift
	    PlatformType_Bowser         = 5,
	    PlatformType_YellowMushroom = 6,
	    PlatformType_WoodSnow       = 7,
	    PlatformType_Sky            = 8,
	    PlatformType_Tower          = 9,
	    PlatformType_Karansha       = 10
    };

public:
    inline PlatformModel() {
        this->scale = 1.0f;
    }

    void init();
    void update(sead::Vec3f& pos, f32 width);
    void draw();

    inline void create(u32 type, u32 width) {
        sead::Vec3i nv3i(0);
        sead::Vec3f nv3f(0);

        this->type = type;
        this->width = width;
        this->rotation = nv3i;
        this->_A0 = nv3f;
        this->init();
    }

    ResArchive* archive;
    ModelWrapper* models[3];
    ModelWrapper* models2[30];
    sead::Vec3f position;
    sead::Vec3f _94;
    sead::Vec3f _A0;
    sead::Vec3f _AC;
    sead::Vec3f _B8;
    sead::Vec3i rotation;
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
