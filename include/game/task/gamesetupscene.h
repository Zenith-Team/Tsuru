#pragma once

#include "sead/task.h"

class GameSetupScene : public sead::CalculateTask {
    SEAD_SINGLETON_TASK(GameSetupScene);

public:
    GameSetupScene(const sead::TaskConstructArg& arg);

    static sead::TaskBase* construct(const sead::TaskConstructArg& arg);

};
