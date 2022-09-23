#include "game/actor/actor.h"
#include "log.h"

class SizeModifierActivator : public Actor {
    SEAD_RTTI_OVERRIDE_IMPL(SizeModifierActivator, Actor);

public:
    SizeModifierActivator(const ActorBuildInfo* buildInfo);
    virtual ~SizeModifierActivator() { }

    static Actor* build(const ActorBuildInfo* buildInfo);
};

const Profile SizeModifierActivatorProfile(&SizeModifierActivator::build, ProfileID::SizeModifierActivator);

SizeModifierActivator::SizeModifierActivator(const ActorBuildInfo* buildInfo)
    : Actor(buildInfo)
{ }

Actor* SizeModifierActivator::build(const ActorBuildInfo* buildInfo) {
    return new SizeModifierActivator(buildInfo);
}
