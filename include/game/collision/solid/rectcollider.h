#pragma once

#include "game/collision/solid/polygoncollider.h"

class RectCollider : public PolygonCollider {
    SEAD_RTTI_OVERRIDE_DECL(RectCollider, PolygonCollider);

public:
    RectCollider() : PolygonCollider(4, points, nodes[0], nodes[1]) {
        for (u32 i = 0; i < 4; i++) {
            points[i].x = 0.0f;
            points[i].y = 0.0f;
        }

        for (u32 i = 0; i < 4; i++) {
            nodes[0][i].flags = this->flags;
            nodes[0][i]._1C = this->_134;
            nodes[1][i].flags = this->flags;
            nodes[1][i]._1C = this->_134;
        }
    }

    virtual ~RectCollider() { }

    bool vf54(u8*, sead::Vector2f*) override;

    sead::Vector2f points[4];
    Node  nodes[2][4];
};
