#pragma once

#include "game/resource/resarchive.h"
#include "game/graphics/model/modelnw.h"

class CharacterModel : public sead::IDisposer { // Size: 0xF0
public:
    CharacterModel(const sead::SafeString& tex, const sead::SafeString& anim);
    virtual ~CharacterModel();

    SEAD_RTTI_BASE(CharacterModel);


    ResArchive* modelResArchive;
    ResArchive* animResArchive;
    ModelWrapper* bodyModel;
    s32 _1C;
    s32 _20;
    s32 _24;
    u32 _28;
    Mtx34 srtMtx;  // Set externally
    Mtx34 srtMtx2; // Copies from srtMtx
    Vec3f _8C;
    Vec3f _98;
    u32 currentCharacter;
    u32 _A8;
    u32 _AC;
    u32 _B0;
    f32 _B4;
    f32 _B8;
    f32 _BC;
    f32 _C0;
    u32 animFlagsArray[3];
    u32 _D0;
    u32 _D4; // Index related to jump anim
    u32 _D8;
    u32 _DC;
    u32 _E0;
    u32 _E4;
    u8 _E8[4]; // Unknown values
    u8 _EC;
};

static_assert(sizeof(CharacterModel) == 0xF0, "CharacterModel size mismatch");

class YoshiModel : public CharacterModel {
public:
    // All green in vanilla
    enum TexColor {
        TexColor_Green,
        TexColor_Pink,
        TexColor_LightBlue,
        TexColor_Yellow
    };

public:
    YoshiModel(TexColor color);
    virtual ~YoshiModel();

    static sead::SafeString texArray[];

    u32 _F0;
    u8 _F4[0x40]; // Is class
    u32 _134;
    f32 _138;
    u8 _13C;
    TexColor color;
    // ...
};
