#pragma once

#include "types.h"
#include "sead.h"
#include "game/container/resarchive.h"

class Animation {
public:
    enum Flags {
        FlagRepeat = 1 << 0,
        FlagUnk2   = 1 << 1,
        FlagIsDone = 1 << 5
    };

    void setRepeat(bool repeat);
    void reset();

    inline bool isAnimationDone() {
        return mFlags & FlagIsDone;
    }

    f32 mStartFrame; // 0    Inited to 0.0
    f32 mEndFrame;   // 4    Inited to 1.0
    f32 _8;          // 8    Inited to 0.0
    f32 _C;          // C    Inited to 1.0
    f32 mFrame;      // 10   Inited to 0.0
    f32 mSpeed;      // 14   Inited to 1.0
    u32 mFlags;      // 18   Inited to FlagRepeat | FlagUnk2
};

class ModelAnimation : public Animation {
public:
    ModelAnimation();
    
    virtual void calculate() = 0;
};

class SkeletalAnimation : public ModelAnimation {
public:
    SkeletalAnimation();

    void calculate() override;

    void init(Model* pModel, ResArchive* pArchive, void* unk, sead::Heap* pHeap);
    void play(ResArchive* pArchive, const sead::SafeString& rIdentifier);

    // nw::g3d::SkeletalAnimObj at 0x20
};

class TextureAnimation : public ModelAnimation {
public:
    TextureAnimation();

    void calculate() override;

    void play(ResArchive* pArchive, const sead::SafeString& rIdentifier);
};

class ShaderAnimation : public ModelAnimation {
public:
    ShaderAnimation();

    void calculate() override;

    void playColorAnim(ResArchive* pArchive, const sead::SafeString& rIdentifier);
    void playTexSrtAnim(ResArchive* pArchive, const sead::SafeString& rIdentifier);
};

class VisibilityAnimation : public ModelAnimation {
public:
    VisibilityAnimation();

    void calculate() override;

    void play(ResArchive* pArchive, const sead::SafeString& rIdentifier);
};

class ShapeAnimation : public ModelAnimation {
public:
    ShapeAnimation();

    void calculate() override;

    void play(ResArchive* pArchive, const sead::SafeString& rIdentifier);
};
