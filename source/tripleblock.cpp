#include "actor/blockbase.h"

#include "model.h"
#include "profileid.h"

// TODO: Finish this lol

class TripleBlock : public BlockBase {
public:
    TripleBlock(const ActorBuildInfo* buildInfo);
    virtual ~TripleBlock() { }

    static BaseActor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onDraw() override;

    void updateModel();

    ModelWrapper* model;

    u8 contentLeft;
    u8 contentCenter;
    u8 contentRight;

    bool multiLeft;
    bool multiCenter;
    bool multiRight;

    bool isUsed;

    void spawnItemUp();
    void spawnItemDown();
    
    void spawnItems();
    void spawnItem(u8 item, bool multi);
    void spawnSwitch(ProfileId::ProfileIdType actorId);
    void spawnBabyYoshiEgg(u8 type);
};

const Profile TripleBlockProfile(&TripleBlock::build, Profile::spriteToProfileList[102], "TripleBlock", nullptr, 0);
PROFILE_RESOURCES(Profile::spriteToProfileList[102], "switch");  // TODO: check if you can add multiple archives to PROFILE_RESOURCES

TripleBlock::TripleBlock(const ActorBuildInfo* buildInfo) : BlockBase(buildInfo) { }

BaseActor* TripleBlock::build(const ActorBuildInfo* buildInfo) {
    return new TripleBlock(buildInfo);
}

u32 TripleBlock::onCreate() {
    if (!init(true, true)) return 2;

    contentLeft = settings >> 24;
    contentCenter = (settings >> 16) & 0xFF;
    contentRight = (settings >> 8) & 0xFF;

    multiLeft = settings & 4;
    multiCenter = settings & 2;
    multiRight = settings & 1;

    Vec2 topLeft(-24.0f, 16.0f);
    Vec2 bottomRight(24.0f, 0.0f);
}
