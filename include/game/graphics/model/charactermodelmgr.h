#pragma once

#include "game/graphics/model/charactermodel.h"

class YoshiModel;

class CharacterModelMgr {
public:
    // This should probably be in PlayerModelMgr
    ENUM_CLASS(Animation,
        Idle = 0,
        Jump = 5,
        Fall = 6,
        TripleJump = 11,
        GroundPound = 16,
        Throw = 33,
        SwimStrokes = 36,
        SwimStrokesFast = 37,
        SwimIdle = 38,
        SwimStand = 41,
        SwimStroke = 42,
        GrabPole = 45,
        PoleIdle = 46,
        PoleClimbing = 47,
        PoleSliding = 48,
        CeilingGrab = 49,
        CeilingIdle = 50,
        CeilingIdleMirrored = 51,
        CeilingMove = 52,
        CeilingMoveMirrored = 53,
        TightropeIdle = 61,
        TightropeStatic = 62,
        TightropeStaticMirrored = 63,
        TightropeDown = 64,
        TightropeUp = 65,
        TightropeDownIdle = 66,
        TightropeDownStatic = 67,
        TightropeJump = 69,
        TightropeLand = 70,
        TightropeDisembark = 71,
        ButtBurn = 81,
        Death = 83,
        DeathFalling = 85,
        CelebrateHat = 91,
        CelebrateTwirl = 92,
        CelebrateFlip = 93,
        CelebrateFlip2 = 94,
        Run = 139,
        IdleStanceLeft = 141,
        IdleStanceRight = 142,
        Run2 = 148,
        IdleStanceRight_2 = 150,
        IdleStanceLeft_2 = 151,
        IdleStanceRight_3 = 152,
        IdleStanceLeft_3 = 153,
        CelebrateTwirl2 = 154,
        Run3 = 166,
        RunSlow = 172,
        RunSlow2 = 173,
        CSIdle = 184,
        CSEnterLevel = 185,
        CelebrateHop = 186,
        CelebratePunch = 187,
        CelebratePunchIdle = 188,
        CelebratePunchUp = 189,
        CelebratePunchUpIdle = 190,
        CelebrateHop2 = 191,
        LoseCry = 193,
        Notice = 202,
        NoticeIdle = 203,
        Notice2 = 204,
        Gaze = 205,
        GazeIdle = 206,
        Bow = 208,
        BowIdle = 209,
        BowLookUp = 210,
        BowLookUpIdle = 211,
        FinalCelebrate = 212,
        CreditsClap = 213,
        CreditsDance = 214,
        CreditsClapSingle = 215,
        Flabbergast = 216,
        FlabbergastIdle = 217,
        Bow2 = 220,
        CreditsStepBob = 221,

        Num = 226
    );

public:
    CharacterModelMgr();

    virtual void vfC(); // nullsub

    void draw();
    void playAnim(CharacterModelMgr::Animation::__type__ anim);

    CharacterModel* modelPtr;   // 0
    u32 _4;                     // 4
  //void* vtable;               // 8
};

class PlayerModelMgr : public CharacterModelMgr { // Size: 0x10
public:
    PlayerModelMgr(u32 character, u32, u32, bool useLightMaps);

    void vfC() override;

    virtual void vf14();
    virtual void vf1C();

    PlayerModel* playerModel;   // C
};

class YoshiModelMgr : public CharacterModelMgr {
public:
    // @param color The color of the Yoshi model
    YoshiModelMgr(YoshiModel::TexColor::__type__ color);

    YoshiModel* yoshiModel;
};

static_assert(sizeof(PlayerModelMgr) == 0x10, "PlayerModelMgr size mismatch");
