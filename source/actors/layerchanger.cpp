#include "game/actor/stage/multistateactor.h"
#include "game/playermgr.h"
#include "game/actor/stage/playerbase.h"
#include "game/eventmgr.h"
#include "log.h"

class LayerChanger : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(LayerChanger, StageActor);
public:
    LayerChanger(const ActorBuildInfo* buildInfo);
    virtual ~LayerChanger() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;

    u8 trigEvent;
    u32 layerDest;
    bool isDone;
    //EventMgr eventmgr;
};

const Profile LayerChangerProfile(&LayerChanger::build, ProfileID::LayerChanger);

LayerChanger::LayerChanger(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
{ }

Actor* LayerChanger::build(const ActorBuildInfo* buildInfo) {
    return new LayerChanger(buildInfo);
}

u32 LayerChanger::onCreate() {
    this->trigEvent = (this->eventID1 & 0xFF) - 1; // nybbles 1-2
    this->layerDest = (this->settings1 >> 0x1C & 0xF); // nybble 5
    this->isDone = false;
    /* Layer chart
    0 - Layer 1
    1 - Layer 2
    2 - Layer 0
    */
    PRINT("Event: ", trigEvent);

    return this->onExecute();
}

u32 LayerChanger::onExecute() {
    if (!EventMgr::instance()->isActive(trigEvent)) {
        this->isDone = false;
        PRINT("Currently checking if Event ID ", trigEvent, " was triggered...");
    } else if (!this->isDone) {
        PRINT("Event ID ", trigEvent, " was triggered");
        for (u32 i = 0; i < 4; i++) {
            Player* player = PlayerMgr::instance()->players[i];
            if (player) {
                PRINT("LAYER SUCCESSFULLY CHANGED");
                player->layer = this->layerDest;
            }
        }
        this->isDone = true;
    }

    if (EventMgr::instance()->isActive(this->eventID1)) {
        PRINT("Event activated");
    }

    return 1;
}
