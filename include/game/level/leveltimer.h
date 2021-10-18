#pragma once

#include <sead.h>

class LevelTimer {
    SEAD_SINGLETON_DISPOSER(LevelTimer)

public:
    LevelTimer();

    s32 shiftTimeLimitLeft();
    s32 shiftTimeLimitRight();

    void setTime(s32 seconds);
    void addTime(s32 seconds);

    // @return Remaining time limit in seconds
    s32 getTimeLimitSeconds() const;

    s32 freezeTimer;        // _10
    s32 timeLimit;          // _14
    s32 startTimeLimit;     // _18
    bool isHurryUp;         // _1C
    u8 flags;               // _1D
    u16 _1E;                // _1E
};
