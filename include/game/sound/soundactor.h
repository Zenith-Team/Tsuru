#pragma once

#include <sead.h>
#include <nw/snd.h>

class SoundActor : public nw::snd::SoundActor {
public:
    u32 _64;
    u32 _68;
    u32 _6C;
    u32 _70;
};

class BasicSoundActor : public SoundActor {
public:
    void* playSound(const char* label, Vec2f* screenPos, u32 unk);

    static BasicSoundActor* GlobalBasicSoundActorA;
    static BasicSoundActor* GlobalBasicSoundActorB;
};

class MovingSoundActor : public SoundActor {
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
