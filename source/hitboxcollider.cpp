/*
    * This file is part of the HitboxCollider header.
    * It has been moved to a seperate .cpp file because it
    * can't be included directly in the header as
    * #pragma once will prevent it from being included
    * as it requires recursive inclusion of header files.
*/

#include "game/actor/stage/stageactor.h"
#include "game/collision/hitboxcollider.h"

void HitboxCollider::getRect(Rect& outRect) {
    Vec3f* ownerPos = &this->owner->position;

    outRect.left   = ownerPos->x + this->colliderInfo.distToCenter.x - this->colliderInfo.distToEdge.x;
    outRect.right  = ownerPos->x + this->colliderInfo.distToCenter.x + this->colliderInfo.distToEdge.x;
    outRect.top    = ownerPos->y + this->colliderInfo.distToCenter.y + this->colliderInfo.distToEdge.y;
    outRect.bottom = ownerPos->y + this->colliderInfo.distToCenter.y - this->colliderInfo.distToEdge.y;
}

bool HitboxCollider::sCollidersOverlap(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    Rect thisRect;
    hcSelf->getRect(thisRect);

    Rect otherRect;
    hcOther->getRect(thisRect);

    return Rect::intersects(thisRect, otherRect);
}
