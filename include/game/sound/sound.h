#pragma once

#include "game/util.h"

#include "game/sound/audiofx.h"
#include "game/sound/effects.h"
#include "game/sound/soundactor.h"
#include "game/sound/soundsystem.h"

extern nw::snd::FxReverbHi::ReverbHiParam DefaultReverbHiParam;
extern nw::snd::FxDelay::DelayParam DefaultDelayParam;

extern f32 SFXReverb_0;
extern f32 SFXReverb_1;
extern f32 SFXReverbPlyJump_0;
extern f32 SFXReverbPlyJump_1;

// Plays a sound at a position
// @param label Name of the sound to be played
// @param position Position to play the sound at
inline void playSound(const char* label, const Vec2f& position) {
    Vec2f screenPos;
    mapPositionToScreen(screenPos, position);
    BasicSoundActor::GlobalBasicSoundActorB->playSound(label, &screenPos, 0);
}

// Plays a sound at a position
// @param label Name of the sound to be played
// @param position Position to play the sound at
inline void playSound(const char* label, const Vec3f& position) {
    Vec2f screenPos;
    mapPositionToScreen(screenPos, Vec2f(position.x, position.y));
    BasicSoundActor::GlobalBasicSoundActorB->playSound(label, &screenPos, 0);
}

// Plays a sound at a position
// @param id Numeric ID of the sound to be played
// @param position Position to play the sound at
inline void playSound(SoundEffects::IDs id, const Vec2f& position) {
    playSound(SoundEffects::getName(id), position);
}

// Plays a sound at a position
// @param id Numeric ID of the sound to be played
// @param position Position to play the sound at
inline void playSound(SoundEffects::IDs id, const Vec3f& position) {
    playSound(SoundEffects::getName(id), position);
}
