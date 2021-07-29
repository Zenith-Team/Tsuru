#pragma once

#include "game/graphics/model/model.h"

class DrawMgr {
public:
    static DrawMgr* sInstance;

    void drawModel(Model* pModel);
    void drawModel(ModelWrapper* pModelWrapper);
    void drawTile(u16 tile, const Vec3f& position, const u32& rotation, const Vec3f& scale);
};
