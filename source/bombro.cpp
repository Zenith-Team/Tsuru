#include "actor/brosbase.h"

#include "drawmgr.h"

class BombBro : public BrosBase {
public:
    BombBro(const ActorBuildInfo* buildInfo);
    virtual ~BombBro() { }

    static ActorBase* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void updateModel();

    ModelWrapper* model;
};

const ActorInfo BombBroActorInfo = { };
const Profile BombBroProfile(&BombBro::build, ProfileId::Sprite572, "BombBro", &BombBroActorInfo, 0);
PROFILE_RESOURCES(ProfileId::Sprite572, "star_coin");


