/*
    * This file is part of the HitboxCollider header.
    * It has been moved to a seperate .cpp file because it
    * can't be included directly in the header as
    * #pragma once will prevent it from being included
    * as it requires recursive inclusion of header files.
*/

#include "game/actor/stage/stageactor.h"
#include "game/collision/hitboxcollider.h"
#include "tsuru/utils.h"

void HitboxCollider::getRect(sead::BoundBox2f& out) {
    sead::Vector3f* ownerPos = &this->owner->position;

    out.setMin(sead::Vector2f(
        ownerPos->x + this->colliderInfo.offset.x - this->colliderInfo.radius.x,
        ownerPos->y + this->colliderInfo.offset.y - this->colliderInfo.radius.y
    ));
    out.setMax(sead::Vector2f(
        ownerPos->x + this->colliderInfo.offset.x + this->colliderInfo.radius.x,
        ownerPos->y + this->colliderInfo.offset.y + this->colliderInfo.radius.y
    ));
}

bool HitboxCollider::sCollidersOverlap(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    sead::BoundBox2f thisRect;
    hcSelf->getRect(thisRect);

    sead::BoundBox2f otherRect;
    hcOther->getRect(otherRect);

    return intersects(thisRect, otherRect);
}
