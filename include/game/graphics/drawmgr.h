#pragma once

#include "game/graphics/model/model.h"

class DrawMgr {
public:
    static DrawMgr* sInstance;

    void drawModel(Model* pModel);
    void drawModel(ModelWrapper* pModelWrapper);
    void drawTile(u16 tile, const Vec3f& rPosition, const u32& rRotation, const Vec3f& rScale);
};
