#pragma once

#include "sead/idisposer.h"
#include "sead/safestring.h"

class MusicPlayer { // Size: 0x74
    SEAD_SINGLETON_DISPOSER(MusicPlayer);

public:
    // Remember to add your custom music to the arrays in musicplayer.cpp
    ENUM_CLASS(MusicIndex,
        Null,
        Chijou,
        Chika,
        Water,
        Athletic,
        Obake,
        Sabaku,
        Yuki,
        Kazan,
        Toride,
        Shiro,
        Hikousen,
        Bonus,
        RoadToLast,
        TorideBoss,
        ShiroBoss,
        Minigame,
        HikousenBoss,
        Mori,
        MGBTL,
        Sanbashi,
        KazanTika,
        Shadow,
        StaffCredit,
        HikousenRouka,
        LastBoss,
        LastBoss2,
        LastBoss2Harp,
        ShiroLast,

        // Start of custom entries

        Num
    );

public:
    MusicPlayer();

    void resetSomeThings();
    void setVolume(f32 volume, u32 frame);
    bool isValidStrmID(s32 id);
    bool shouldHurryUp();
    const char* getSeqName(s32 id);
    const char* getStrmName(s32 id);

private:
    void initMembers();

public:

    static const char* strmListNormal[MusicIndex::Num];
    static const char* strmListFast[MusicIndex::Num];

    static const char* seqListNormal[MusicIndex::Num];
    static const char* seqListFast[MusicIndex::Num];

    s32 streamID;           // Inited to -1
    const char* strmName;   // Inited to "SE_DUMMY"
    const char* seqName;    // Inited to "SE_DUMMY"
    u32 soundType;          // Inited to 0
    u32 _20;                // Inited to 0
    u32 _24;                // Inited to 0
    u32 _28;                // Inited to 0
    u32 _2C;                // Inited to 0
    u32 _30;                // Inited to 0
    u32 _34;                // Inited to 0
    const char* sfxName;    // Inited to "SE_DUMMY"
    const char* sfxName_2;  // Inited to "SE_DUMMY"
    f32 volume;             // Inited to 1.0f
    f32 _44;                // Inited to 1.0f
    u8 _48;                 // Inited to 1
    u32 _4C;                // Inited to 0
    u32 _50;                // Inited to 0
    u32 _54;                // Inited to 0
    const char* strmName_2; // Inited to "STRM_BGM_DUMMY"
    u8 _5C;                 // Inited to 1
    s32 _60;                // Inited to -1
    u32 _64;                // Inited to 1
    u32 _68;                // Inited to 0xF
    u32 _6C;                // Inited to 0
    f32 _70;                // Inited to 1.0f
};

static_assert(sizeof(MusicPlayer) == 0x74, "MusicPlayer size mismatch");
