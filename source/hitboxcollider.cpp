#include "actor/stageactor.h"
#include "hitboxcollider.h"

void HitboxCollider::getRect(Rect& outRect) {
    Vec3* ownerPos = &this->owner->position;

    outRect.left   = ownerPos->x + this->info.distToCenter.x - this->info.distToEdge.x;
    outRect.right  = ownerPos->x + this->info.distToCenter.x + this->info.distToEdge.x;
    outRect.top    = ownerPos->y + this->info.distToCenter.y + this->info.distToEdge.y;
    outRect.bottom = ownerPos->y + this->info.distToCenter.y - this->info.distToEdge.y;
}

bool HitboxCollider::collidersOverlap(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    Rect thisRect;
    hcSelf->getRect(thisRect);

    Rect otherRect;
    hcOther->getRect(otherRect);

    return Rect::RectsOverlap(thisRect, otherRect);
}
