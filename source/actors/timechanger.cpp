#include "game/task/coursetask.h"
#include "game/actor/stage/stageactor.h"
#include "game/task/taskmgr.h"
#include "game/level/leveltimer.h"
#include "game/eventmgr.h"
#include "log.h"

class TimeChanger : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(TimeChanger, StageActor);

public:
    TimeChanger(const ActorBuildInfo* buildInfo);
    virtual ~TimeChanger() { }

    u32 eventId;
    u32 time;
    u32 timeMode;

    bool activated; 

    u32 onCreate() override;
    u32 onExecute() override;
};

REGISTER_PROFILE(TimeChanger, ProfileID::TimeChanger);

TimeChanger::TimeChanger(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
{ }

u32 TimeChanger::onCreate() {
    this->activated = false;

    this->eventId = this->eventID1 - 1;

    // time uses 3 nybbles 
    this->time = this->settings2 >> 0x14 & 0xFFF; 

    // 0 = add 1 = subtract 2 = set
    this->timeMode = this-> settings1 >> 0x10 & 0xF;

    return this->onExecute();
}

u32 TimeChanger::onExecute() {
    if (this->activated) return 1;

    if (EventMgr::instance()->isActive(this->eventId)) {
        switch (this->timeMode) {
            case 0: {
                LevelTimer::instance()->addTime(this->time);
                break;
            }
            case 1: {
                LevelTimer::instance()->addTime(-static_cast<s32>(this->time));
                break;
            }
            // This cannot be used until setTime is implemented in LevelTimer
            //case 2: { 
            //    LevelTimer::instance()->setTime(this->time);
            //    break;
            //}
            default: {
                PRINT("[TimeChanger] ", "Invalid time mode.");
                break;
            }
        }

        this->activated = true;

        PRINT("[TimeChanger] ", (this->timeMode == 0 ? "Added " : this->timeMode == 1 ? "Subtracted " : "Set "), this->time, " seconds to the timer.");
    }

    return 1;
}