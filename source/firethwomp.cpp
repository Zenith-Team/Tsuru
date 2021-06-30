#include "actor/thwomp.h"

class FireThwomp : public Thwomp {
public:
    FireThwomp(const ActorBuildInfo* buildInfo);
    virtual ~FireThwomp() { }

    static BaseActor* build(const ActorBuildInfo* buildInfo);
};

const ActorInfo FireThwompActorInfo = { Vec2i(16, -32), Vec2i(0, 0), Vec2i(2, 8), 0, 48, 0, 0, 32 };
const Profile FireThwompProfile(&FireThwomp::build, Profile::spriteToProfileList[405], "FireThwomp", &FireThwompActorInfo, 0x116);
PROFILE_RESOURCES(Profile::spriteToProfileList[405], "dossun");

FireThwomp::FireThwomp(const ActorBuildInfo* buildInfo) : Thwomp(buildInfo) { }

BaseActor* FireThwomp::build(const ActorBuildInfo* buildInfo) {
    return new FireThwomp(buildInfo);
}
