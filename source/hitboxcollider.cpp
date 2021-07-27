#include "game/actor/stageactor.h"
#include "game/collision/hitboxcollider.h"

void HitboxCollider::getRect(Rect& outRect) {
    Vec3f* ownerPos = &this->mOwner->mPosition;

    outRect.left   = ownerPos->x + this->mColliderInfo.mDistToCenter.x - this->mColliderInfo.mDistToEdge.x;
    outRect.right  = ownerPos->x + this->mColliderInfo.mDistToCenter.x + this->mColliderInfo.mDistToEdge.x;
    outRect.top    = ownerPos->y + this->mColliderInfo.mDistToCenter.y + this->mColliderInfo.mDistToEdge.y;
    outRect.bottom = ownerPos->y + this->mColliderInfo.mDistToCenter.y - this->mColliderInfo.mDistToEdge.y;
}

bool HitboxCollider::sCollidersOverlap(HitboxCollider* pHCSelf, HitboxCollider* pHCOther) {
    Rect thisRect;
    pHCSelf->getRect(thisRect);

    Rect otherRect;
    pHCOther->getRect(thisRect);

    return Rect::RectsOverlap(thisRect, otherRect);
}
