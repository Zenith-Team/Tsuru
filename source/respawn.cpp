#include <game/task/taskmgr.h>
#include <game/task/courseselecttask.h>
#include <game/level/levelinfo.h>
#include <tsuru/tsurusavemgr.h>

void respawn() {
    if (TsuruSaveMgr::sSaveData.instantRespawnEnabled)
        TaskMgr::instance()->startLevel(CourseSelectTask::instance(), LevelInfo::instance()->world, LevelInfo::instance()->level);
}
