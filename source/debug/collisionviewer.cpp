#include <game/task/areatask.h>
#include <game/task/courseselecttask.h>
#include <game/collision/collidermgr.h>
#include <game/collision/solid/shapedcollider.h>
#include <game/collision/solid/circularcollider.h>
#include <game/collision/solid/solidontopcollider.h>
#include <game/collision/actorphysicsmgr.h>
#include <game/actor/actormgr.h>
#include <game/actor/courseselect/cscollisionactor.h>
#include <game/collision/cshitboxcollider.h>
#include <agl/lyr/renderinfo.h>
#include <log.h>

#include <custom/cheatmgr.h>

void drawLine(const Vec2f& position, const f32 rotation, const sead::Color4f& color, const f32 lineLength, const f32 lineThickness) {
    Vec3f scale(lineLength, lineThickness, 1.0f);
    Vec3f rot(0.0f, 0.0f, rotation);
    Vec3f pos(position.x + (lineLength * cosf(rotation)) / 2, position.y + (lineLength * sinf(rotation)) / 2, 4000.0f);

    Mtx34 mtx;
    Mtx34::makeSRT(mtx, scale, rot, pos);
    sead::PrimitiveRenderer::instance()->mRendererImpl->drawQuadImpl(mtx, color, color);
}

void drawLine(const Vec2f& point1, const Vec2f& point2, const sead::Color4f& color, const f32 lineThickness) {
    f32 length = sqrtf(powf(point1.x - point2.x, 2) + powf(point1.y - point2.y, 2));

    const Vec2f& leftPoint = (point1.x < point2.x) ? point1 : point2;
    const Vec2f& rightPoint = (&leftPoint == &point1) ? point2 : point1;
    f32 angle = atan2f(rightPoint.y - leftPoint.y, rightPoint.x - leftPoint.x);

    drawLine(leftPoint, angle, color, length, lineThickness);
}

void AreaTask::drawLayerDebug(const agl::lyr::RenderInfo& renderInfo) {
    this->drawLayer3D(renderInfo);

    if (CheatMgr::sInstance.mCollisionViewerEnabled) {
        sead::PrimitiveRenderer::instance()->setCamera(*renderInfo.mCamera);
        sead::PrimitiveRenderer::instance()->setProjection(*renderInfo.mProjection);
        sead::PrimitiveRenderer::instance()->begin();

        HitboxCollider::List::Node* hColliderNode;
        hColliderNode = HitboxColliderMgr::instance()->mActiveList.mFirst;

        while (hColliderNode != nullptr) {
            HitboxCollider* hCollider = hColliderNode->mOwner;

            if ((hCollider->mColliderInfo._1C & 0x800) == 0) {
                Rect rect;
                hCollider->getRect(rect);

                if (hCollider->mColliderInfo.mShape == HitboxCollider::ShapeRectangle) {
                    Vec2f point1(rect.left, rect.top);
                    Vec2f point2(rect.right, rect.top);
                    Vec2f point3(rect.right, rect.bottom);
                    Vec2f point4(rect.left, rect.bottom);

                    drawLine(point1, point2, sead::colorRed, 1.0f);
                    drawLine(point2, point3, sead::colorRed, 1.0f);
                    drawLine(point3, point4, sead::colorRed, 1.0f);
                    drawLine(point1, point4, sead::colorRed, 1.0f);
                    drawLine(point1, point3, sead::colorRed, 1.0f);   // Diagonal line
                }

                else if (hCollider->mColliderInfo.mShape == HitboxCollider::ShapeCircle) {
                    f32 radius = (rect.right - rect.left) / 2.0f;

                    sead::PrimitiveRenderer::instance()->drawCircle32(Vec3f(rect.left + radius, rect.bottom + radius, 4000.0f), radius, sead::colorRed);
                }
            }

            hColliderNode = hColliderNode->mNext;
        }

        hColliderNode = HitboxColliderMgr::instance()->_34.mFirst;

        while (hColliderNode != nullptr) {
            HitboxCollider* hCollider = hColliderNode->mOwner;

            Rect rect;
            hCollider->getRect(rect);

            if (hCollider->mColliderInfo.mShape == HitboxCollider::ShapeRectangle) {
                Vec2f point1(rect.left, rect.top);
                Vec2f point2(rect.right, rect.top);
                Vec2f point3(rect.right, rect.bottom);
                Vec2f point4(rect.left, rect.bottom);

                drawLine(point1, point2, sead::colorRed, 1.0f);
                drawLine(point2, point3, sead::colorRed, 1.0f);
                drawLine(point3, point4, sead::colorRed, 1.0f);
                drawLine(point1, point4, sead::colorRed, 1.0f);
                drawLine(point1, point3, sead::colorRed, 1.0f); // Diagonal line
            }

            else if (hCollider->mColliderInfo.mShape == HitboxCollider::ShapeCircle) {
                f32 radius = (rect.right - rect.left) / 2.0f;

                sead::PrimitiveRenderer::instance()->drawCircle32(Vec3f(rect.left + radius, rect.bottom + radius, 4000.0f), radius, sead::colorRed);
            }

            hColliderNode = hColliderNode->mNext;
        }

        ColliderBase::List* activeList = &ColliderMgr::instance()->mLists[0];
        ColliderBase::List::Node* node = activeList->mFirst;

        while (node != nullptr) {
            ColliderBase* colliderBase = node->mOwner;
            if (sead::IsDerivedFrom<CircularCollider, ColliderBase>(colliderBase)) {
                CircularCollider* collider = static_cast<CircularCollider*>(colliderBase);

                sead::PrimitiveRenderer::instance()->drawCircle32(Vec3f(collider->mOwnerInfo.mPosition->x + collider->mDistToCenter.x + collider->_160.x, collider->mOwnerInfo.mPosition->y + collider->mDistToCenter.y + collider->_160.y, 4000.f), collider->mRadius, sead::colorBlue);
            }

            else if (sead::IsDerivedFrom<SolidOnTopCollider, ColliderBase>(colliderBase)) {
                SolidOnTopCollider* collider = static_cast<SolidOnTopCollider*>(colliderBase);
                if (collider->mPoints.mSize < 2)
                    continue;
                
                const Vec2f center = Vec2f((*collider->mOwnerInfo.mPosition).x, (*collider->mOwnerInfo.mPosition).y) + collider->mDistToCenter;

                for (u32 i = 0; i < collider->mNodes1.mSize; i++) {
                    const ColliderBase::Node& node = collider->mNodes1[i];
                    drawLine(center + node.mSensor.mPoint1, center + node.mSensor.mPoint2, sead::colorGreen, 1.0f);
                }
            }

            else if(sead::IsDerivedFrom<ShapedCollider, ColliderBase>(colliderBase)) {
                ShapedCollider* collider = static_cast<ShapedCollider*>(colliderBase);
                if (collider->mPoints.mSize < 2)
                    continue;
                
                const Vec2f center = Vec2f((*collider->mOwnerInfo.mPosition).x, (*collider->mOwnerInfo.mPosition).y) + collider->mDistToCenter;

                for (u32 i = 0; i < collider->mNodes1.mSize; i++) {
                    const ColliderBase::Node& node = collider->mNodes1[i];
                    drawLine(center + node.mSensor.mPoint1, center + node.mSensor.mPoint2, sead::colorBlue, 1.0f);
                }

                if (collider->mPoints.mSize >= 4 && !(collider->mPoints.mSize & 1)) {
                    const ColliderBase::Node& node1 = collider->mNodes1[0];
                    const ColliderBase::Node& node2 = collider->mNodes1[collider->mPoints.mSize / 2 - 1];
                    drawLine(center + node1.mSensor.mPoint1, center + node2.mSensor.mPoint2, sead::colorBlue, 1.0f);
                }
            }

            else if (CheatMgr::sInstance.mDebugLoggingEnabled) {
                LOG("Found unknown collider for actor with id: 0x%x, and profile id: 0x%x\n", colliderBase->mOwner->mID, colliderBase->mOwner->mProfile->mID);
            }

            node = node->mNext;
        }

        ActorBuffer* actors = &ActorMgr::instance()->mActors;
        for (u32 i = 0; i < actors->mBuffer.mSize; i++) {
            StageActor* actor = sead::DynamicCast<StageActor, Actor>(actors->mBuffer[i]);
            if (actor == NULL || !actor->mIsVisible || actor->mIsDeleted)
                continue;
            
            ActorPhysicsMgr* actorPhysicsMgr = actor->getActorPhysicsMgr();
            if (actorPhysicsMgr == NULL || actorPhysicsMgr->mPosition == NULL)
                continue;
            
            for (u32 j = 0; j < 4; j++) {
                const ActorPhysicsMgr::Sensor* sensor = actorPhysicsMgr->getSensor(j);
                if (sensor == nullptr)
                    continue;
                
                f32 p1 = sensor->mPoint1;
                f32 p2 = sensor->mPoint2;

                if (p1 == p2) {
                    p1 -= 0.5f;
                    p2 += 0.5f;
                }

                if (j < 2) {
                    Vec2f point1(actorPhysicsMgr->mPosition->x + sensor->mDistanceFromCenter, actorPhysicsMgr->mPosition->y + p1);
                    Vec2f point2(actorPhysicsMgr->mPosition->x + sensor->mDistanceFromCenter, actorPhysicsMgr->mPosition->y + p2);

                    drawLine(point1, point2, sead::colorYellow, 1.0f);
                }

                else {
                    Vec2f point1(actorPhysicsMgr->mPosition->x + p1, actorPhysicsMgr->mPosition->y + sensor->mDistanceFromCenter);
                    Vec2f point2(actorPhysicsMgr->mPosition->x + p2, actorPhysicsMgr->mPosition->y + sensor->mDistanceFromCenter);

                    drawLine(point1, point2, (j == 2) ? sead::colorWhite : sead::colorCyan, 1.0f);
                }
            }
        }

        sead::PrimitiveRenderer::instance()->end();
    }
}

void CourseSelectTask::drawLayerDebug(const agl::lyr::RenderInfo& renderInfo) {
    this->drawLayer3D(renderInfo);

    if (CheatMgr::sInstance.mCollisionViewerEnabled) {
        sead::PrimitiveRenderer::instance()->setCamera(*renderInfo.mCamera);
        sead::PrimitiveRenderer::instance()->setProjection(*renderInfo.mProjection);
        sead::PrimitiveRenderer::instance()->begin();

        for (u32 i = 0; i < CSHitboxColliderMgr::instance()->mArray1.mPtrNum; i++) {
            CSHitboxCollider* cshCollider = static_cast<CSHitboxCollider*>(CSHitboxColliderMgr::instance()->mArray1.mPtrs[i]);

            if (!cshCollider)
                continue;

            CourseSelectActor* actor = reinterpret_cast<CourseSelectActor*>(ActorMgr::instance()->mActors.findActorByID(&cshCollider->mOwnerID));

            if (!actor)
                continue;

            sead::PrimitiveRenderer::instance()->drawCube(actor->mPosition + cshCollider->mInfo.mOffset, cshCollider->mInfo.mSize, sead::colorYellow);
        }


        for (u32 i = 0; i < CSHitboxColliderMgr::instance()->mArray2.mPtrNum; i++) {
            CSHitboxCollider* cshCollider = static_cast<CSHitboxCollider*>(CSHitboxColliderMgr::instance()->mArray2.mPtrs[i]);

            if (!cshCollider)
                continue;

            CourseSelectActor* actor = reinterpret_cast<CourseSelectActor*>(ActorMgr::instance()->mActors.findActorByID(&cshCollider->mOwnerID));

            if (!actor)
                continue;

            sead::PrimitiveRenderer::instance()->drawCube(actor->mPosition + cshCollider->mInfo.mOffset, cshCollider->mInfo.mSize, sead::colorRed);
        }

        sead::PrimitiveRenderer::instance()->end();
    }
}
