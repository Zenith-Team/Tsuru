#pragma once

#include "game/audio/gameaudio.h"
#include "game/sound/effects.h"
#include "game/sound/sndobject.h"

// Plays a sound at a position
// @param label Name of the sound to be played
// @param position Position to play the sound at
inline void playSound(const char* label, const Vec2f& position) {
    Vec2f screenPos;
    GameAudio::convertSndObjectPos(&screenPos, position);
    GameAudio::SndObjectCommonMap::instance()->startSound(label, screenPos, 0);
}

// Plays a sound at a position
// @param label Name of the sound to be played
// @param position Position to play the sound at
inline void playSound(const char* label, const Vec3f& position) {
    playSound(label, Vec2f(position.x, position.y));
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
