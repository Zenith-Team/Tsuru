#include "game/actor/stage/multistateactor.h"
#include "game/playermgr.h"
#include "game/actor/stage/playerbase.h"
#include "game/eventmgr.h"
#include "tsuru/log.h"

class LayerChanger : public StageActor {
    SEAD_RTTI_OVERRIDE(LayerChanger, StageActor);
public:
    LayerChanger(const ActorBuildInfo* buildInfo);
    virtual ~LayerChanger() { }

    u32 onCreate() override;
    u32 onExecute() override;

    u8 trigEvent;
    u32 layerDest;
    bool isDone;
};

REGISTER_PROFILE(LayerChanger, ProfileID::LayerChanger);

LayerChanger::LayerChanger(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
{ }

u32 LayerChanger::onCreate() {
    this->trigEvent = (this->eventID1 & 0xFF) - 1; // nybbles 1-2
    this->layerDest = (this->settings1 >> 0x1C & 0xF); // nybble 5
    this->isDone = false;

    /* Layer chart
    0 - Layer 1
    1 - Layer 2
    2 - Layer 0
    */

    return this->onExecute();
}

u32 LayerChanger::onExecute() {
    if (!EventMgr::instance()->isActive(trigEvent)) {
        this->isDone = false;
    } else if (!this->isDone) {
        for (u32 i = 0; i < 4; i++) {
            Player* player = PlayerMgr::instance()->players[i];
            if (player) {
                player->layer = this->layerDest;
            }
        }

        this->isDone = true;
    }

    return 1;
}
