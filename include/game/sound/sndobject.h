#pragma once

#include "nw/snd/soundhandle.h"
#include "nw/snd/soundactor.h"
#include "heap/seadDisposer.h"
#include "math/seadVector.h"

class AudAudioPlayer;

class Snd2DCalc { };

static_assert(sizeof(Snd2DCalc) == 0x1, "Snd2DCalc size mismatch");

class SndObjectBase : public nw::snd::SoundActor {
public:
    enum ObjType {
        ObjType_0,
        ObjType_1,
        ObjType_2
    };

public:
    SndObjectBase(ObjType objType, AudAudioPlayer* audioPlayer);
    virtual ~SndObjectBase();

    // isPlaying() ?
    virtual bool vf34(const char* label, s32 playerIdx);

    u32 numHandles;         // Inited to 0
    u32 remotePlayer;       // Inited to 1
    Snd2DCalc* snd2DCalc;
    ObjType objType;
};

static_assert(sizeof(SndObjectBase) == 0x74, "SndObjectBase size mismatch");

template <s32 PlayableSoundCount>
class SndObject : public SndObjectBase {
public:
    // Idk if this inherits nw::snd::SoundHandle or just has it as a member
    class SoundHandlePrm : public sead::IDisposer, public nw::snd::SoundHandle {
    public:
        f32 _14;
    };

    static_assert(sizeof(SoundHandlePrm) == 0x18, "SndObject::SoundHandlePrm size mismatch");

public:
    SndObject(ObjType objType, u32 remotePlayer);
    virtual ~SndObject(); // deleted

    virtual void vf3C(); // deleted
    virtual void vf44(); // deleted
    virtual void vf4C(); // deleted
    virtual void vf54(); // deleted
    virtual void vf5C(); // deleted
    virtual void vf64(); // deleted
    virtual void vf6C(); // deleted

    nw::snd::SoundHandle* startSound(const char* label, u32 remotePlayer);

    f32 _74;
    u32 _78;
    f32 _7C;
    f32 _80;
    SoundHandlePrm handles[6];
    sead::Vector2f position; // Screen position
};

static_assert(sizeof(SndObject<1>) == 0x11C, "SndObject size mismatch");

template <s32 PlayableSoundCount>
class SndObjectCommon : public SndObjectBase {
public:
    // Idk if this inherits nw::snd::SoundHandle or just has it as a member
    class SoundHandlePrm : public nw::snd::SoundHandle {
    public:
        SoundHandlePrm();
        ~SoundHandlePrm();

        s32 _4;
        u8 _8[0x4];
        f32 _C;
        u32 _10;
    };

    static_assert(sizeof(SoundHandlePrm) == 0x14, "SndObjectCommon::SoundHandlePrm size mismatch");

public:
    SndObjectCommon(u32 remotePlayer);
    virtual ~SndObjectCommon(); // deleted

    // Does the stagePos -> screenPos conversion
    virtual nw::snd::SoundHandle* startSoundStage(const char* label, const sead::Vector2f& stagePos, u32 remotePlayer); // deleted
    // Does the stagePos -> screenPos conversion
    virtual nw::snd::SoundHandle* startSoundStage(const char* label, const sead::Vector2f& stagePos, u16, u32 remotePlayer); // deleted

    nw::snd::SoundHandle* startSound(const char* label, const sead::Vector2f& screenPos, u32 remotePlayer);
    nw::snd::SoundHandle* startSound(const char* label, const sead::Vector2f& screenPos, u16, u32 remotePlayer);
    
    nw::snd::SoundHandle* holdSound(const char* label, s32 id, const sead::Vector2f& screenPos, u32 remotePlayer);
    nw::snd::SoundHandle* holdSound(const char* label, s32 id, const sead::Vector2f& screenPos, u16, u32 remotePlayer);

    SoundHandlePrm handles[14];
};

static_assert(sizeof(SndObjectCommon<1>) == 0x18C, "SndObjectCommon size mismatch");
