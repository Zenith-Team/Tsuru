#include <game/actor/stage/stageactor.h>
#include <game/profile/profileid.h>
#include <game/eventmgr.h>
#include <game/graphics/tilerenderer.h>
#include <dynlibs/os/functions.h>

class TileCorruptor : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(TileCorruptor, StageActor)

public:
    TileCorruptor(const ActorBuildInfo* buildInfo);
    virtual ~TileCorruptor() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
};

const Profile TileCorruptorProfile(&TileCorruptor::build, ProfileID::TileCorruptor, "TileCorruptor", nullptr, 0);

TileCorruptor::TileCorruptor(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
{ }

Actor* TileCorruptor::build(const ActorBuildInfo* buildInfo) {
    return new TileCorruptor(buildInfo);
}

u32 TileCorruptor::onCreate() {
    OSBlockSet(&(TileRenderer::instance()->tileMasks._0[0]), 0, sizeof(TileRenderer::instance()->tileMasks._0));

    return 1;
}
