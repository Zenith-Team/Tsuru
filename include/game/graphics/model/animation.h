#pragma once

#include "sead/heap.h"
#include "sead/safestring.h"
#include "game/resource/resarchive.h"

class Animation {
public:
    enum Flags {
        Flag_Repeat = 1 << 0,
        Flag_Unk1   = 1 << 1,
        Flag_IsDone = 1 << 5
    };

    // Sets if the animation should loop
    // @param repeat Whether or not the animation should loop
    void shouldLoop(bool loop);
    // Resets the animation
    void reset();

    // Checks if the animation has completed playback
    // @return Whether or not the animation has completed playback
    inline bool isAnimationDone() const {
        return flags & Flag_IsDone;
    }

    // Checks if the animation loops
    // @return Whether or not the animation loops
    inline bool isAnimationLooping() const {
        return flags & Flag_Repeat;
    }

    f32 startFrame;  // 0    Inited to 0.0
    f32 endFrame;    // 4    Inited to 1.0
    f32 _8;          // 8    Inited to 0.0
    f32 _C;          // C    Inited to 1.0
    f32 frame;       // 10   Inited to 0.0
    f32 speed;       // 14   Inited to 1.0
    u32 flags;       // 18   Inited to FlagRepeat | FlagUnk2
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

    void init(Model* model, ResArchive* archive, void* unk, sead::Heap* heap);
    void play(ResArchive* archive, const sead::SafeString& identifier);

    // nw::g3d::SkeletalAnimObj at 0x20
};

class TextureAnimation : public ModelAnimation {
public:
    TextureAnimation();

    void calculate() override;

    void play(ResArchive* archive, const sead::SafeString& identifier);
};

class ShaderAnimation : public ModelAnimation {
public:
    ShaderAnimation();

    void calculate() override;

    void playColorAnim(ResArchive* archive, const sead::SafeString& identifier);
    void playTexSrtAnim(ResArchive* archive, const sead::SafeString& identifier);
};

class VisibilityAnimation : public ModelAnimation {
public:
    VisibilityAnimation();

    void calculate() override;

    void play(ResArchive* archive, const sead::SafeString& identifier);
};

class ShapeAnimation : public ModelAnimation {
public:
    ShapeAnimation();

    void calculate() override;

    void play(ResArchive* archive, const sead::SafeString& identifier);
};
