#pragma once

#include "sead.h"

class MusicPlayer : public sead::IDisposer
{
public:
    MusicPlayer();
    ~MusicPlayer();

    // Incomplete
    bool shouldHurryUp();
    bool isValidStrmID(s32 strmID);
    const char* getStrmNameForID(s32 strmID);
    const char* getSeqNameForID(s32 strmID);

    s32 streamID;
    const char* strmName;
    const char* seqName;
    u32 soundType;
    u32 _20;
    u32 _24;
    u8 _28;
    u8 _29;
    u8 _2A;
    u8 _2B;
    u32 _2C;
    u32 _30;
    u32 _34;
    const char* SEName;
    const char* SEName2;
    f32 _40;
    f32 _44;
    u8 _48;
    u8 _49;
    u8 _4A;
    u8 _4B;
    u32 _4C;
    u32 _50;
    u32 _54;
    const char* strmName2;
    u32 _5C;
    s32 _60;
    u32 _64;
    u32 _68;
    u32 _6C;
    f32 _70;

    static const u32 NUM_MUSIC_LIST = 29;

    static const char* strmListNormal[NUM_MUSIC_LIST];
    static const char* strmListFast[NUM_MUSIC_LIST];

    static const char* seqListNormal[NUM_MUSIC_LIST];
    static const char* seqListFast[NUM_MUSIC_LIST];
};
