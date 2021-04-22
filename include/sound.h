#pragma once

#include "nw/snd.h"
#include "sead.h"
#include "util/vec2.h"


class AudioFx {
public:
    nw::snd::internal::FxReverbHiParam& getReverbHiParam();
    nw::snd::internal::FxDelayParam&    getDelayParam();
};

class SoundSystemBase {
public:
    AudioFx* getAudioFx();
};

class SoundSystem : public SoundSystemBase {
    SEAD_SINGLETON_DISPOSER(SoundSystem)

public:
    nw::snd::SoundArchive* getSoundArchive();
    
    inline const char* GetItemLabel(u32 id) { return getSoundArchive()->GetItemLabel(id); }
    inline u32 GetItemId(const char* label) { return getSoundArchive()->GetItemId(label); }
};

class SoundActor : public nw::snd::SoundActor {
public:
    u32 _64;
    u32 _68;
    u32 _6C;
    u32 _70;
};

class BasicSoundActor : public SoundActor {
public:
    static BasicSoundActor* instance;

    void* playSound(const char* label, Vec2* screenPos, u32 unk);
};

// Both are dereived classes from BasicSoundActor
extern BasicSoundActor* GlobalBasicSoundActorA;
extern BasicSoundActor* GlobalBasicSoundActorB;

class MovingSoundActor : public SoundActor {  // size: 0x8C
public:
    class Handle : public sead::IDisposer {
    public:
        u32 _10;
        f32 _14;
    };

public:
    MovingSoundActor(u32 unk1, u32 unk2);
    void setPosition(const Vec2& position);

    f32 _74;
    u32 _78;
    f32 _7C;
    f32 _80;
    Handle handles[6];  // 84
    Vec2 _114;          // 114  position i think
};

// Convenience

void mapPositionToScreen(Vec2& out, const Vec2& position);

inline void PlaySound(const char* label, const Vec2& position) {
    Vec2 screenPos;
    mapPositionToScreen(screenPos, position);
    GlobalBasicSoundActorA->playSound(label, &screenPos, 0);
}
