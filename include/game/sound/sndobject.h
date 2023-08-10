#pragma once

#include "nw/snd.h"
#include "sead/idisposer.h"

class Snd2DCalc { };

static_assert(sizeof(Snd2DCalc) == 0x1, "Snd2DCalc size mismatch");

class SndObjectBase : public nw::snd::SoundActor {
public:
    enum ObjType {
        ObjType_0,
        ObjType_1
    };

public:
    // Second param is a class that has nw::snd::SoundArchivePlayer at 0x4
    SndObjectBase(ObjType objType, void*);
    virtual ~SndObjectBase();

    virtual u8 vf34(const char*, s32);

    u32 numHandles;         // Inited to 0
    u32 remotePlayer;       // Inited to 1
    Snd2DCalc* snd2DCalc;
    ObjType objType;
};

static_assert(sizeof(SndObjectBase) == 0x74, "SndObjectBase size mismatch");

template <s32 PlayableSoundCount>
class SndObjectCommon : public SndObjectBase {
public:
    class SoundHandlePrm : public nw::snd::SoundHandle {
    public:
        SoundHandlePrm();
        ~SoundHandlePrm();

        s32 _4;
        u8 _8[0x4];
        f32 _C;
        u32 _10;
    };

    static_assert(sizeof(SoundHandlePrm) == 0x14, "SndObjectCommon::SoundHanldePrm size mismatch");

public:
    SndObjectCommon(u32 remotePlayer);
    virtual ~SndObjectCommon(); // deleted

    // Does the stagePos -> screenPos conversion
    virtual SoundHandlePrm* startSoundStage(const char* label, const Vec2f& stagePos, u32 remotePlayer); // deleted
    // Does the stagePos -> screenPos conversion
    virtual SoundHandlePrm* startSoundStage(const char* label, const Vec2f& stagePos, u16, u32 remotePlayer); // deleted

    SoundHandlePrm* startSound(const char* label, const Vec2f& screenPos, u32 remotePlayer);
    SoundHandlePrm* startSound(const char* label, const Vec2f& screenPos, u16, u32 remotePlayer);
    
    SoundHandlePrm* holdSound(const char* label, s32 id, const Vec2f& screenPos, u32 remotePlayer);
    SoundHandlePrm* holdSound(const char* label, s32 id, const Vec2f& screenPos, u16, u32 remotePlayer);

    SoundHandlePrm handles[14];
};

static_assert(sizeof(SndObjectCommon<1>) == 0x18C, "SndObjectCommon size mismatch");

// TODO
class MovingSoundActor : public SndObjectBase {
public:
    class Handle : public sead::IDisposer {
    public:
        u32 _10;
        f32 _14;
    };

public:
    MovingSoundActor(u32 unk1, u32 unk2);

    void setPosition(const Vec2f& position);

    f32 _74;
    u32 _78;
    f32 _7C;
    f32 _80;
    Handle handles[6];
    Vec2f _114;
};
