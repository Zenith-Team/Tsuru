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

    s32 getTimeLimitSeconds() const;

    s32 mFreezeTimer;       // _10
    s32 mTimeLimit;         // _14
    s32 mStartTimeLimit;    // _18
    bool mIsHurryUp;        // _1C
    u8 mFlags;              // _1D
    u16 _1E;                // _1E
};
