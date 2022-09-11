#pragma once

#include "sead/heap.h"
#include "sead/safestring.h"
#include "game/resource/resarchive.h"

class FrameCtrl {
public:
    FrameCtrl();

    void reset();
    void shouldLoop(bool loop);
    void play();

    bool checkFrame(f32) const;

    ENUM_CLASS(Flags,
        Repeat = 1 << 0,
        Unk1   = 1 << 1,
        IsDone = 1 << 5
    );

    bool isDone() const {
        return this->flags.bits & Flags::IsDone;
    }

    bool isLooping() const {
        return this->flags.bits & Flags::Repeat;
    }

    f32 startFrame;
    f32 endFrame;
    f32 _8;
    f32 frameMax;
    f32 currentFrame;
    f32 speed;
    sead::BitFlag32 flags;
};

class Animation {
public:
    Animation();

    virtual void calc() = 0;

    FrameCtrl frameCtrl;
};

class SkeletalAnimation : public Animation {
public:
    SkeletalAnimation();

    void calc() override;

    void init(Model* model, ResArchive* archive, void* unk, sead::Heap* heap);
    void play(ResArchive* archive, const sead::SafeString& identifier);

};

class TextureAnimation : public Animation {
public:
    TextureAnimation();

    void calc() override;

    void play(ResArchive* archive, const sead::SafeString& identifier);
};

class ShaderAnimation : public Animation {
public:
    ShaderAnimation();

    void calc() override;

    void playColorAnim(ResArchive* archive, const sead::SafeString& identifier);
    void playTexSrtAnim(ResArchive* archive, const sead::SafeString& identifier);
};

class VisibilityAnimation : public Animation {
public:
    VisibilityAnimation();

    void calc() override;

    void play(ResArchive* archive, const sead::SafeString& identifier);
};

class ShapeAnimation : public Animation {
public:
    ShapeAnimation();

    void calc() override;

    void play(ResArchive* archive, const sead::SafeString& identifier);
};
