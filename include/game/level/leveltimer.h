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

    s32 freezeTimer;        // 10
    s32 timeLimit;          // 14
    s32 startTimeLimit;     // 18
    bool isHurryUp;         // 1C
    u8 flags;               // 1D
    u16 _1E;                // 1E
};
