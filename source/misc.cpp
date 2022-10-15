#include "game/task/taskmgr.h"
#include "game/task/coursetask.h"
#include "game/level/levelinfo.h"
#include "tsuru/save/managers/tsurusavemgr.h"
#include "sead/graphicscontext.h"
#include "log.h"

fmt::_Hex hex;
bool fmt::_hexActive = false;

void respawn() {
    if (TsuruSaveMgr::sSaveData.instantRespawnEnabled) {
        TaskMgr::instance()->startLevel(CourseTask::instance(), LevelInfo::instance()->world, LevelInfo::instance()->level);
    }
}

// Always a copy of the currently applied graphics context
// NEVER write to this, only read
volatile sead::GraphicsContext CurrentGraphicsContext;
