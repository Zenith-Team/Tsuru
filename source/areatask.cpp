#include "areatask.h"
#include "level.h"

extern f32 PlayerJumpArc;
extern f32 MiniPlayerJumpArc;
extern f32 PlayerJumpMax;
extern f32 PlayerDescentRate;

void AreaTask::readHaxxOptions()
{
    this->wrapFlag = 0;

    Level::Area* area = Level::instance->getArea(LevelInfo::instance->area);
    Level::Area::Options* areaOptions = reinterpret_cast<Level::Area::Options*>(area->blocks[1]);

    if (areaOptions->wrapByte & 1)
        this->wrapFlag = 1;

    if (areaOptions->wrapByte & 2)
    {
        PlayerJumpArc = 0.5f;
        MiniPlayerJumpArc = 0.5f;
        PlayerJumpMax = 4.5f;
        PlayerDescentRate = -2.0f;
    }

    else
    {
        PlayerJumpArc = 2.5f;
        MiniPlayerJumpArc = 2.5f;
        PlayerJumpMax = 3.628f;
        PlayerDescentRate = -4.0f;
    }
}
