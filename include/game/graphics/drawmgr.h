#pragma once

#include <game/graphics/model/model.h>

class DrawMgr {
    SEAD_SINGLETON_DISPOSER(DrawMgr)

public:
    void drawModel(Model* model);
    void drawModel(ModelWrapper* modelWrapper);
    void drawTile(u16 tile, const Vec3f& position, const u32& rotation, const Vec3f& scale);
};
