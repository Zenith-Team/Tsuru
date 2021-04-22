#pragma once

#include "model.h"

class DrawMgr {
public:
    static DrawMgr* instance;

    void drawModel(Model* model);
    void drawModel(ModelWrapper* modelWrapper);
    void drawTile(u16 tile, const Vec3& position, const u32& rotation, const Vec3& scale);
};
