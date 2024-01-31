#pragma once

#include "heap/seadDisposer.h"

class LevelCamera {
    SEAD_SINGLETON_DISPOSER(LevelCamera);

public:
    f32 zoom;                  // 10
    f32 _14;                   // 14
    sead::BoundBox2f zoneBox;  // 18
    sead::BoundBox2f _28[4];   // 28
    f32 cameraWidth;           // 68
    f32 cameraHeight;          // 6C
    f32 cameraLeft;            // 70
    f32 cameraCenterX;         // 74
    f32 cameraRight;           // 78
    f32 cameraTop;             // 7C
    f32 cameraCenterY;         // 80
    f32 cameraBottom;          // 84
    // ...
};
