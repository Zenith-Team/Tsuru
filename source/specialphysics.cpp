#include <game/task/areatask.h>
#include <game/level/level.h>
#include <game/level/levelinfo.h>

extern f32 PlayerJumpArc;
extern f32 MiniPlayerJumpArc;
extern f32 PlayerJumpMax;
extern f32 PlayerDescentRate;

enum WrapFlags {
    Wrap        = 1 << 0,
    LowGravity  = 1 << 1
};

void AreaTask::setPhysicsValues() {
    Level::Area* area = Level::instance()->getArea(LevelInfo::instance()->area);
    Level::Area::Options* areaOptions = reinterpret_cast<Level::Area::Options*>(area->blocks[1]);

    if (areaOptions->wrapValue & Wrap) {
        this->wrapFlag = 1;
    }

    else if (areaOptions->wrapValue & LowGravity) {
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
