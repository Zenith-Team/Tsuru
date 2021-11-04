#pragma once

#include <game/container/resarchive.h>

class CharacterModel : public sead::IDisposer { // Size: 0xF0
public:
    CharacterModel(const sead::SafeString& tex, const sead::SafeString& anim);
    virtual ~CharacterModel();

    // TODO: Virtual functions

    ResArchive* texArchive;
    ResArchive* animArchive;
    u32 _18;
    s32 _1C;
    s32 _20;
    s32 _24;
    u32 _28;
    u8 _2C[0x30]; // new thing
    u8 _5C[0x30]; // new thing
    Vec3f _8C;
    Vec3f _98;
    u32 _A4;
    u32 _A8;
    u32 _AC;
    u32 _B0;
    f32 _B4;
    f32 _B8;
    f32 _BC;
    f32 _C0;
    u32 _C4;
    u8 _C8[12]; // Unknown values
    u32 _D4;
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

    static sead::SafeString texArray[4];

    u32 _F0;
    u8 _F4[0x40]; // Is class
    u32 _134;
    f32 _138;
    u8 _13C;
    TexColor color;
    // ...
};
