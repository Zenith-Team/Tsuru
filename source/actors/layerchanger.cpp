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
    u32 onDraw() override;

    u8 trigEvent;
    u32 layerDest;
    bool isDone;
    // u8 destEvent; // temp
    PlayerBase* player;

    EventMgr eventmgr;
};

// stuffs
const Profile LayerChangerProfile(&LayerChanger::build, ProfileID::LayerChanger);

LayerChanger::LayerChanger(const ActorBuildInfo* buildInfo) 
    : StageActor(buildInfo)
{ }

Actor* LayerChanger::build(const ActorBuildInfo* buildInfo) {
    return new LayerChanger(buildInfo);
}

u32 LayerChanger::onCreate() {
    // this->trigEvent = (this->eventID1 >> 0x4 & 0xF); // nybble 1
    this->trigEvent = (this->eventID1 & 0xFF); // nybbles 1-2
    // this->trigEvent = (eventID1);
    // this->trigEvent = 1;
    this->layerDest = (this->settings1 >> 0x1C & 0xF); // nybble 5
    this->isDone = false;
    /* Layer chart
    0 - Layer 1
    1 - Layer 2
    2 - Layer 0
    */
   LOG("Event: %d", trigEvent);
   LOG("StageActorEvent: %d", eventID1);
   
//    return this->onExecute();
   return 1;
}

u32 LayerChanger::onExecute() {
    // if (!this->isDone) {
        // LOG("Currently checking if Event ID %d was triggered...", trigEvent);
        // if (EventMgr::instance()->isActive(this->trigEvent)) {
            // this->isDone = true;
            // LOG("Event ID %d was triggered", trigEvent);
            // for (u32 i = 0; i < 4; i++) {
                // player = PlayerMgr::instance()->players[i];
                // if (player) {
                    // player->layer = this->layerDest;
                // }
            // }
        // }
    // }

    if (EventMgr::instance()->isActive(this->eventID1)) {
        LOG("Event activated");
    }
    return 1;
}

u32 LayerChanger::onDraw() {
    return 1;
}