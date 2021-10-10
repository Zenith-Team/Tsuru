#include <game/task/taskmgr.h>
#include <game/task/coursetask.h>
#include <game/level/levelinfo.h>
#include <tsuru/save/tsurusavemgr.h>

void respawn() {
    if (TsuruSaveMgr::sSaveData.instantRespawnEnabled)
        TaskMgr::instance()->startLevel(CourseTask::instance(), LevelInfo::instance()->world, LevelInfo::instance()->level);
}
