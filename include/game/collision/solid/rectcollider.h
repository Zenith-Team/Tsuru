#pragma once

#include "game/collision/solid/shapedcollider.h"

class RectCollider : public ShapedCollider {
    SEAD_RTTI_OVERRIDE(RectCollider, ShapedCollider)

public:
    forceinline RectCollider()
        : ShapedCollider(4, mPoints, mNodes[0], mNodes[1])
    {
        for (u32 i = 0; i < 4; i++) {
            mPoints[i].x = 0.0f;
            mPoints[i].y = 0.0f;
        }

        for (u32 i = 0; i < 4; i++) {
            mNodes[0][i].mFlags = this->mFlags;
            mNodes[0][i]._1C = this->_134;
            mNodes[1][i].mFlags = this->mFlags;
            mNodes[1][i]._1C = this->_134;
        }
    }

    virtual ~RectCollider() { }

    bool vf54(u8*, Vec2f*) override;

    Vec2f mPoints[4];
    Node mNodes[2][4];
};
