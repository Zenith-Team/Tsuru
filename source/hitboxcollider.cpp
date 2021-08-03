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
    Vec3f* ownerPos = &this->mOwner->mPosition;

    outRect.left   = ownerPos->x + this->mColliderInfo.mDistToCenter.x - this->mColliderInfo.mDistToEdge.x;
    outRect.right  = ownerPos->x + this->mColliderInfo.mDistToCenter.x + this->mColliderInfo.mDistToEdge.x;
    outRect.top    = ownerPos->y + this->mColliderInfo.mDistToCenter.y + this->mColliderInfo.mDistToEdge.y;
    outRect.bottom = ownerPos->y + this->mColliderInfo.mDistToCenter.y - this->mColliderInfo.mDistToEdge.y;
}

bool HitboxCollider::sCollidersOverlap(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    Rect thisRect;
    hcSelf->getRect(thisRect);

    Rect otherRect;
    hcOther->getRect(thisRect);

    return Rect::RectsOverlap(thisRect, otherRect);
}
