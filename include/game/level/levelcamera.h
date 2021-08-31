#pragma once

#include <sead.h>

class LevelCamera : public sead::IDisposer {
public:
    static LevelCamera* sInstance;

	f32 _10;                // 10
	f32 _14;                // 14
	Rect mZoneBox;          // 18
	Rect _28[4];            // 28
	f32 mCameraWidth;       // 68
	f32 mCameraHeight;      // 6C
	f32 mCameraLeft;        // 70
	f32 mCameraCenterX;     // 74
	f32 mCameraRight;       // 78
	f32 mCameraTop;         // 7C
	f32 mCameraCenterY;     // 80
	f32 mCameraBottom;      // 84
    //...
};
