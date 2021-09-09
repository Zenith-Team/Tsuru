#pragma once

#include <sead.h>

class LevelCamera {
	SEAD_SINGLETON_DISPOSER(LevelCamera)

public:
	f32 _10;                // 10
	f32 _14;                // 14
	Rect zoneBox;           // 18
	Rect _28[4];            // 28
	f32 cameraWidth;        // 68
	f32 cameraHeight;       // 6C
	f32 cameraLeft;         // 70
	f32 cameraCenterX;      // 74
	f32 cameraRight;        // 78
	f32 cameraTop;          // 7C
	f32 cameraCenterY;      // 80
	f32 cameraBottom;       // 84
    //...
};
