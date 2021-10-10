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
#include <tsuru/save/tsurusavemgr.h>
#include <utils/mtx.h>

void drawLine3D(const Vec3f& position, const u32 rotation, const sead::Color4f& color, const f32 lineLength, const f32 lineThickness) {
    Vec3f scale(lineLength, lineThickness, lineThickness);
    Vec3u rot(0x80000000, (rotation + 0x40000000) * -1, 0x00000000);
    f32 rotSin;
    f32 rotCos;
    sinCosIdx(&rotSin, &rotCos, rotation);
    Vec3f pos(position.x + (lineLength * rotSin) / 2, position.y, position.z + (lineLength * rotCos) / 2);

    Mtx34 mtx;
    mtx.makeSRzxyTIdx(scale, rot, pos);
    sead::PrimitiveRenderer::instance()->rendererImpl->drawCubeImpl(mtx, color, color);
}

void drawLine(const Vec2f& position, const f32 rotation, const sead::Color4f& color, const f32 lineLength, const f32 lineThickness) {
    Vec3f scale(lineLength, lineThickness, 1.0f);
    Vec3f rot(0.0f, 0.0f, rotation);
    Vec3f pos(position.x + (lineLength * cosf(rotation)) / 2, position.y + (lineLength * sinf(rotation)) / 2, 4000.0f);

    Mtx34 mtx;
    Mtx34::makeSRT(mtx, scale, rot, pos);
    sead::PrimitiveRenderer::instance()->rendererImpl->drawQuadImpl(mtx, color, color);
}

void drawLine(const Vec2f& point1, const Vec2f& point2, const sead::Color4f& color, const f32 lineThickness) {
    f32 length = sqrtf(powf(point1.x - point2.x, 2) + powf(point1.y - point2.y, 2));

    const Vec2f& leftPoint = (point1.x < point2.x) ? point1 : point2;
    const Vec2f& rightPoint = (&leftPoint == &point1) ? point2 : point1;
    f32 angle = atan2f(rightPoint.y - leftPoint.y, rightPoint.x - leftPoint.x);

    drawLine(leftPoint, angle, color, length, lineThickness);
}

void AreaTask::renderCollisions(const agl::lyr::RenderInfo& renderInfo) {
    this->drawLayer3D(renderInfo);

    if (TsuruSaveMgr::sSaveData.collisionViewerEnabled) {
        sead::PrimitiveRenderer::instance()->setCamera(*renderInfo.camera);
        sead::PrimitiveRenderer::instance()->setProjection(*renderInfo.projection);
        sead::PrimitiveRenderer::instance()->begin();

        HitboxCollider::List::Node* hColliderNode;
        hColliderNode = HitboxColliderMgr::instance()->activeList.first;

        while (hColliderNode != nullptr) {
            HitboxCollider* hCollider = hColliderNode->owner;

            if ((hCollider->colliderInfo._1C & 0x800) == 0) {
                Rect rect;
                hCollider->getRect(rect);

                if (hCollider->colliderInfo.shape == HitboxCollider::HitboxShape_Rectangle) {
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

                else if (hCollider->colliderInfo.shape == HitboxCollider::HitboxShape_Circle) {
                    f32 radius = (rect.right - rect.left) / 2.0f;

                    sead::PrimitiveRenderer::instance()->drawCircle32(Vec3f(rect.left + radius, rect.bottom + radius, 4000.0f), radius, sead::colorRed);
                }
            }

            hColliderNode = hColliderNode->next;
        }

        hColliderNode = HitboxColliderMgr::instance()->_34.first;

        while (hColliderNode != nullptr) {
            HitboxCollider* hCollider = hColliderNode->owner;

            Rect rect;
            hCollider->getRect(rect);

            if (hCollider->colliderInfo.shape == HitboxCollider::HitboxShape_Rectangle) {
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

            else if (hCollider->colliderInfo.shape == HitboxCollider::HitboxShape_Circle) {
                f32 radius = (rect.right - rect.left) / 2.0f;

                sead::PrimitiveRenderer::instance()->drawCircle32(Vec3f(rect.left + radius, rect.bottom + radius, 4000.0f), radius, sead::colorRed);
            }

            hColliderNode = hColliderNode->next;
        }

        ColliderBase::List* activeList = &ColliderMgr::instance()->lists[0];
        ColliderBase::List::Node* node = activeList->first;

        while (node != nullptr) {
            ColliderBase* colliderBase = node->owner;
            if (sead::IsDerivedFrom<CircularCollider, ColliderBase>(colliderBase)) {
                CircularCollider* collider = static_cast<CircularCollider*>(colliderBase);

                sead::PrimitiveRenderer::instance()->drawCircle32(Vec3f(collider->ownerInfo.position->x + collider->distToCenter.x + collider->_160.x, collider->ownerInfo.position->y + collider->distToCenter.y + collider->_160.y, 4000.f), collider->radius, sead::colorBlue);
            }

            else if (sead::IsDerivedFrom<SolidOnTopCollider, ColliderBase>(colliderBase)) {
                SolidOnTopCollider* collider = static_cast<SolidOnTopCollider*>(colliderBase);
                if (collider->points.size < 2)
                    continue;

                const Vec2f center = Vec2f((*collider->ownerInfo.position).x, (*collider->ownerInfo.position).y) + collider->distToCenter;

                for (u32 i = 0; i < collider->nodes1.size; i++) {
                    const ColliderBase::Node& node = collider->nodes1[i];
                    drawLine(center + node.sensor.point1, center + node.sensor.point2, sead::colorGreen, 1.0f);
                }
            }

            else if (sead::IsDerivedFrom<ShapedCollider, ColliderBase>(colliderBase)) {
                ShapedCollider* collider = static_cast<ShapedCollider*>(colliderBase);
                if (collider->points.size < 2)
                    continue;

                const Vec2f center = Vec2f((*collider->ownerInfo.position).x, (*collider->ownerInfo.position).y) + collider->distToCenter;

                for (u32 i = 0; i < collider->nodes1.size; i++) {
                    const ColliderBase::Node& node = collider->nodes1[i];
                    drawLine(center + node.sensor.point1, center + node.sensor.point2, sead::colorBlue, 1.0f);
                }

                if (collider->points.size >= 4 && !(collider->points.size & 1)) {
                    const ColliderBase::Node& node1 = collider->nodes1[0];
                    const ColliderBase::Node& node2 = collider->nodes1[collider->points.size / 2 - 1];
                    drawLine(center + node1.sensor.point1, center + node2.sensor.point2, sead::colorBlue, 1.0f);
                }
            }

            else {
                // LOG("Found unknown collider for actor with id: 0x%x, and profile id: 0x%x\n", colliderBase->owner->ID, colliderBase->owner->profile->ID);
            }

            node = node->next;
        }

        ActorBuffer* actors = &ActorMgr::instance()->actors;
        for (u32 i = 0; i < actors->startBuffer.size; i++) {
            StageActor* actor = sead::DynamicCast<StageActor, Actor>(actors->startBuffer[i]);
            if (actor == NULL || !actor->isVisible || actor->isDeleted)
                continue;

            ActorPhysicsMgr* actorPhysicsMgr = actor->getActorPhysicsMgr();
            if (actorPhysicsMgr == NULL || actorPhysicsMgr->position == NULL)
                continue;

            for (u32 j = 0; j < 4; j++) {
                const ActorPhysicsMgr::Sensor* sensor = actorPhysicsMgr->getSensor(j);
                if (sensor == nullptr)
                    continue;

                f32 p1 = sensor->point1;
                f32 p2 = sensor->point2;

                if (p1 == p2) {
                    p1 -= 0.5f;
                    p2 += 0.5f;
                }

                if (j < 2) {
                    Vec2f point1(actorPhysicsMgr->position->x + sensor->distanceFromCenter, actorPhysicsMgr->position->y + p1);
                    Vec2f point2(actorPhysicsMgr->position->x + sensor->distanceFromCenter, actorPhysicsMgr->position->y + p2);

                    drawLine(point1, point2, sead::colorYellow, 1.0f);
                }

                else {
                    Vec2f point1(actorPhysicsMgr->position->x + p1, actorPhysicsMgr->position->y + sensor->distanceFromCenter);
                    Vec2f point2(actorPhysicsMgr->position->x + p2, actorPhysicsMgr->position->y + sensor->distanceFromCenter);

                    drawLine(point1, point2, (j == 2) ? sead::colorWhite : sead::colorCyan, 1.0f);
                }
            }
        }

        sead::PrimitiveRenderer::instance()->end();
    }
}

void CourseSelectTask::renderCollisions(const agl::lyr::RenderInfo& renderInfo) {
    this->drawLayer3D(renderInfo);

    if (TsuruSaveMgr::sSaveData.collisionViewerEnabled) {
        sead::PrimitiveRenderer::instance()->setCamera(*renderInfo.camera);
        sead::PrimitiveRenderer::instance()->setProjection(*renderInfo.projection);
        sead::PrimitiveRenderer::instance()->begin();

        for (u32 i = 0; i < CSHitboxColliderMgr::instance()->array1.ptrNum; i++) {
            CSHitboxCollider* cshCollider = static_cast<CSHitboxCollider*>(CSHitboxColliderMgr::instance()->array1.ptrs[i]);

            if (!cshCollider)
                continue;

            CourseSelectActor* actor = reinterpret_cast<CourseSelectActor*>(ActorMgr::instance()->actors.findActorByID(&cshCollider->ownerID));

            if (!actor)
                continue;

            sead::PrimitiveRenderer::instance()->drawCube(actor->position + cshCollider->info.offset, cshCollider->info.size, sead::colorYellow);
        }

        for (u32 i = 0; i < CSHitboxColliderMgr::instance()->array2.ptrNum; i++) {
            CSHitboxCollider* cshCollider = static_cast<CSHitboxCollider*>(CSHitboxColliderMgr::instance()->array2.ptrs[i]);

            if (!cshCollider)
                continue;

            CourseSelectActor* actor = reinterpret_cast<CourseSelectActor*>(ActorMgr::instance()->actors.findActorByID(&cshCollider->ownerID));

            if (!actor)
                continue;

            sead::PrimitiveRenderer::instance()->drawCube(actor->position + cshCollider->info.offset, cshCollider->info.size, sead::colorRed);
        }

        Actor** current = ActorMgr::instance()->actors.startBuffer.buffer;
        while (current < ActorMgr::instance()->actors.endBuffer.buffer) {
            Actor* actor = *current;
            if (actor) {
                CourseSelectActor* csactor = static_cast<CourseSelectActor*>(actor);
                drawLine3D(csactor->position, csactor->rotation, sead::colorMagenta, 128.0f, 4.0f);
            }
            current++;
        }

        sead::PrimitiveRenderer::instance()->end();
    }
}
