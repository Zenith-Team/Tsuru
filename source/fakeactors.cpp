#include "actor/actor.h"

#include "sound.h"
#include "effect.h"
#include "misctemp.h"

void fakeStarCoin(Actor* starCoin) {
    Vec2 screenPos;
    Vec2 starCoinPos(starCoin->position.x, starCoin->position.y);
    mapPosToScreen(&screenPos, &starCoinPos);
    BasicSoundActor::instance->playSound("SE_OBJ_DDOOR_OPEN", &screenPos, 1);

    Vec3 pos(starCoin->position.x, starCoin->position.y - 12, starCoin->position.z);
    Effect::spawn(RP_ObakeDoor_Disapp, &pos, 0, 0);

    starCoin->isDeleted = true;
}
