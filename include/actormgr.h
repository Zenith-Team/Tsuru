#pragma once

#include "actor/base.h"

class ActorMgr
{
public:
    /* "addToActive":
       0: add to actorsToCreate
       1: add to activeActors and drawableActors
       else: don't add to any of the lists */
    Base* create(ActorBuildInfo* buildInfo, u32 addToActive);

    static ActorMgr* instance;

    // ...
};
