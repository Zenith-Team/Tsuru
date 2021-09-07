#pragma once

#include <game/util.h>

#include <game/sound/audiofx.h>
#include <game/sound/soundactor.h>
#include <game/sound/soundsystem.h>

extern const char** sfxArray[1040];

extern BasicSoundActor* GlobalBasicSoundActorA;
extern BasicSoundActor* GlobalBasicSoundActorB;

inline void PlaySound(const char* label, const Vec2f& position) {
    Vec2f screenPos;
    mapPositionToScreen(screenPos, position);
    GlobalBasicSoundActorA->playSound(label, &screenPos, 0);
}
