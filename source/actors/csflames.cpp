#include "game/actor/courseselect/cscollisionactor.h"
#include "game/csplayermgr.h"
#include "game/actor/actormgr.h"
#include "game/graphics/model/modelnw.h"
#include "game/csscriptmgr.h"
#include "game/savemgr.h"
#include "game/effect/effect.h"
#include "log.h"

class CSFlames : public CourseSelectActor {
    SEAD_RTTI_OVERRIDE(CSFlames, CourseSelectActor);

public:
    CSFlames(const ActorBuildInfo* buildInfo);
    virtual ~CSFlames() { }

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override { return 1; }

    EffectWrapper fx;
};

REGISTER_PROFILE(CSFlames, ProfileID::CSFlames);

CSFlames::CSFlames(const ActorBuildInfo* buildInfo)
    : CourseSelectActor(buildInfo)
    , fx()
{ }

u32 CSFlames::onCreate() {
    return this->onExecute();
}

u32 CSFlames::onExecute() {
    sead::Vector3f scale = sead::Vector3f(8.0f, 8.0f, 8.0f);
    this->fx.update(RP_Cmn_FireballHit, &this->position, nullptr, &scale);

    return 1;
}
