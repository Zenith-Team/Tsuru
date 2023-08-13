#pragma once

#include "agl/lyr/layer.h"

class Model;
class ModelWrapper;

class DrawMgr {
    SEAD_SINGLETON_DISPOSER(DrawMgr);

public:
    // Draws a model to the screen
    // @param model Pointer to a model to be drawn
    void drawModel(Model* model);
    // Draws a model to the screen via a ModelWrapper
    // @param modelWrapper pointer to the model wrapper to draw
    void drawModel(ModelWrapper* modelWrapper);
    // Draws a tile to the screen
    // @param u16 Tile object id to be drawn
    // @param position Position to draw the tile at
    // @param rotation Rotation to be applied to the tile
    // @param scale Scale to be applied to the tile
    void drawTile(u16 tile, const Vec3f& position, const u32& rotation, const Vec3f& scale);

    void setTargetLayer(agl::lyr::Layer* layer, u32);
    void resetTargetLayer();
};
