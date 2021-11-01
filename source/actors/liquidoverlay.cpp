#include <game/actor/stage/stageactor.h>
#include <game/actor/stage/player.h>
#include <game/level/level.h>
#include <game/level/levelinfo.h>
#include <game/playermgr.h>
#include <game/actor/actormgr.h>

class LiquidOverlay : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(LiquidOverlay, StageActor)

public:
    LiquidOverlay(const ActorBuildInfo* buildInfo);
    virtual ~LiquidOverlay() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;

    void doOverlayCollision(u32 index, Player* player);

    u32 timers[4];
    Rect targetLiquidLocation;
};

const Profile LiquidOverlayProfile(&LiquidOverlay::build, ProfileID::LiquidOverlay, "LiquidOverlay", nullptr, 0);

LiquidOverlay::LiquidOverlay(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
    , timers()
    , targetLiquidLocation()
{ }

Actor* LiquidOverlay::build(const ActorBuildInfo* buildInfo) {
    return new LiquidOverlay(buildInfo);
}

u32 LiquidOverlay::onCreate() {
    // Retrieve the target location containing the liquid by the ID in nybble 5
    Level::instance()->getArea(LevelInfo::instance()->area)->getLocation(this->targetLiquidLocation, this->settings1 >> 0x1C & 0xF);

    return 1;
}

u32 LiquidOverlay::onExecute() {
    for (u32 i = 0; i < 4; i++) {
        Player* player = PlayerMgr::instance()->players[i];
        if (player) {
            // Nybble 7
            if ((this->settings1 >> 0x14 & 0xF) != 1) { // Location mode
                Rect playerRect;
                player->getRect(playerRect);
                if (Rect::intersects(playerRect, this->targetLiquidLocation))
                    this->doOverlayCollision(i, player);
                else
                    timers[i] = 0;
            } else { // Zone-wide mode
                Actor** currentActor = ActorMgr::instance()->actors.start.buffer;
                while (currentActor < ActorMgr::instance()->actors.end.buffer) {
                    if (*currentActor && (*currentActor)->profile->id == 84) { // Water
                        StageActor* water = static_cast<StageActor*>(*currentActor);
                        if (player->position.y <= water->position.y)
                            this->doOverlayCollision(i, player);
                        else
                            timers[i] = 0;
                    }

                    currentActor++;
                }
            }
        }
    }

    return 1;
}

void LiquidOverlay::doOverlayCollision(u32 i, Player* player) {
    if (this->timers[i]++ >= 240) {

        switch (this->settings1 >> 0x18 & 0xF) { // Nybble 6, damage type
            default: case 0: player->damage(0, Player::DamageType_Ice); break;
        }

        this->timers[i] = 0;
    }
}
