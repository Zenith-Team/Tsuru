#include "game/actor/stage/stageactor.h"
#include "game/task/areatask.h"
#include "game/actor/stage/player.h"
#include "game/eventmgr.h"
#include "log.h"

extern "C" PlayerGravityData* LoadCustomPlayerGravity() {
    static PlayerGravityData normalGravity[2] = {
        {
            -0.34f,
            {
                2.5f, 1.5f, 0.3f, -0.12f, -3.0f
            },
            {
                -0.34f, -0.34f, -0.34f, -0.25f, -0.34f, -0.34f
            },
            {
                -0.06f, -0.25f, -0.34f, -0.08f, -0.31f, -0.34f
            }
        },
        {
            -0.09f,
            {
                2.5f, 1.5f, 0.0f, -2.0f, -2.0f
            },
            {
                -0.09f, -0.09f, -0.09f, -0.06f, -0.09f, -0.09f
            },
            {
                -0.04f, -0.06f, -0.09f, -0.06f, -0.09f, -0.09f
            }
        }
    };

    static PlayerGravityData lowGravity[2] = {
        {
            -0.03f,
            {
                12.5f, 11.5f, 10.3f, -10.12f, -13.0f
            },
            {
                -0.17f, -0.17f, -0.17f, -0.175f, -0.17f, -0.17f
            },
            {
                -0.03f, -0.175f, -0.17f, -0.04f, -0.155f, -0.17f
            }
        },
        {
            -0.09f,
            {
                2.5f, 1.5f, 0.0f, -2.0f, -2.0f
            },
            {
                -0.09f, -0.09f, -0.09f, -0.06f, -0.09f, -0.09f
            },
            {
                -0.04f, -0.06f, -0.09f, -0.06f, -0.09f, -0.09f
            }
        }
    };

    if (AreaTask::instance() && AreaTask::instance()->flags & AreaTask::Flag::LowGravity) {
        return lowGravity;
    } else {
        return normalGravity;
    }
}

class PhysicsModifier : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(PhysicsModifier, StageActor);

public:
    PhysicsModifier(const ActorBuildInfo* buildInfo);
    virtual ~PhysicsModifier() { }

    u32 onCreate() override;
    u32 onExecute() override;

    bool active;
};

REGISTER_PROFILE(PhysicsModifier, ProfileID::PhysicsModifier);

PhysicsModifier::PhysicsModifier(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
    , active(false)
{ }

u32 PhysicsModifier::onCreate() {
    if (!this->eventID1) {
        return 2;
    }

    return this->onExecute();
}

u32 PhysicsModifier::onExecute() {
    if (EventMgr::instance()->isActive(this->eventID1 - 1)) {
        if (!this->active) {
            this->active = true;

            AreaTask::instance()->flags |= AreaTask::Flag::LowGravity;

            PRINT(AreaTask::instance()->flags);
        }
    } else {
        this->active = false;

        AreaTask::instance()->flags &= ~AreaTask::Flag::LowGravity;
    }

    return 1;
}
