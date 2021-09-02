#include <game/task/areatask.h>
#include <game/level/level.h>
#include <game/level/levelinfo.h>

extern f32 PlayerJumpArc;
extern f32 MiniPlayerJumpArc;
extern f32 PlayerJumpMax;
extern f32 PlayerDescentRate;

void AreaTask::readOptions() {
    Level::Area* area = Level::instance()->getArea(LevelInfo::instance()->mArea);
    Level::Area::Options* areaOptions = reinterpret_cast<Level::Area::Options*>(area->mBlocks[1]);

    // Wrap flag set to "wrap" 
    if (areaOptions->mWrapByte & 1)
        this->mWrapFlag = 1;

    // Wrap flag set to "low-gravity"
    else if (areaOptions->mWrapByte & 2) {
        PlayerJumpArc = 0.5f;
        MiniPlayerJumpArc = 0.5f;
        PlayerJumpMax = 4.5f;
        PlayerDescentRate = -2.0f;
    }

    // Wrap flag set to "wrap + low-gravity"
    else if (areaOptions->mWrapByte & 3) {
        this->mWrapFlag = 1;

        PlayerJumpArc = 0.5f;
        MiniPlayerJumpArc = 0.5f;
        PlayerJumpMax = 4.5f;
        PlayerDescentRate = -2.0f;
    }

    // Wrap flag not set
    else {
        this->mWrapFlag = 0;

        PlayerJumpArc = 2.5f;
        MiniPlayerJumpArc = 2.5f;
        PlayerJumpMax = 3.628f;
        PlayerDescentRate = -4.0f;
    }
}
