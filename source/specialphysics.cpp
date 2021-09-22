#include <game/task/areatask.h>
#include <game/level/level.h>
#include <game/level/levelinfo.h>

extern f32 PlayerJumpArc;
extern f32 MiniPlayerJumpArc;
extern f32 PlayerJumpMax;
extern f32 PlayerDescentRate;

void AreaTask::setPhysicsValues() {
    Level::Area* area = Level::instance()->getArea(LevelInfo::instance()->area);
    Level::Area::Options* areaOptions = reinterpret_cast<Level::Area::Options*>(area->blocks[1]);

    // Wrap flag set to "wrap"
    if (areaOptions->wrapValue & 1) this->wrapFlag = 1;

    // Wrap flag set to "low-gravity"
    else if (areaOptions->wrapValue & 2) {
        PlayerJumpArc = 0.5f;
        MiniPlayerJumpArc = 0.5f;
        PlayerJumpMax = 4.5f;
        PlayerDescentRate = -2.0f;
    }

    // Wrap flag set to "wrap + low-gravity"
    else if (areaOptions->wrapValue & 3) {
        this->wrapFlag = 1;

        PlayerJumpArc = 0.5f;
        MiniPlayerJumpArc = 0.5f;
        PlayerJumpMax = 4.5f;
        PlayerDescentRate = -2.0f;
    }

    // Wrap flag not set
    else {
        this->wrapFlag = 0;

        PlayerJumpArc = 2.5f;
        MiniPlayerJumpArc = 2.5f;
        PlayerJumpMax = 3.628f;
        PlayerDescentRate = -4.0f;
    }
}
