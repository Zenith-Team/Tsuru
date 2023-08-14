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

    u32 onCreate() override;
    u32 onExecute() override;

    u32 eventId;
    u32 time;
    u32 timeMode;
    bool triggered;
};

REGISTER_PROFILE(TimeChanger, ProfileID::TimeChanger);

TimeChanger::TimeChanger(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
{ }

u32 TimeChanger::onCreate() {
    this->eventId = this->eventID1 - 1;

    // time uses 3 nybbles 
    this->time = this->settings2 >> 0x14 & 0xFFF; 

    // 0 = add 1 = subtract 2 = set
    this->timeMode = this->settings1 >> 0x10 & 0xF;

    return this->onExecute();
}

u32 TimeChanger::onExecute() {
    if (!EventMgr::instance()->isActive(this->eventId)) {
        this->triggered = false;
    } else if (!this->triggered) {
        switch (this->timeMode) {
            default: {
                LevelTimer::instance()->addTime(this->time);
                break;
            }
            case 1: {
                LevelTimer::instance()->addTime(-static_cast<s32>(this->time));
                break;
            }
            case 2: { 
                LevelTimer::instance()->setTime(this->time);
                break;
            }
        }
    
        this->triggered = true;
        if (!(this->settings1 & 0x10)) {
            this->isDeleted = true;
        }
    }

    return 1;
}
