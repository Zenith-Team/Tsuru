#pragma once

#include "agl/lyr/layer.h"

class LayerAgl : public agl::lyr::Layer {
    SEAD_RTTI_OVERRIDE(LayerAgl, agl::lyr::Layer)
    // Base class for all game layer classes
public:
    class Node {
        SEAD_RTTI_BASE(Node)

    public:
        virtual void Calc() = 0;
    };

public:
    LayerAgl();
    virtual ~LayerAgl();

    void doInitialize(sead::Heap* heap) override;
    void vf3C() override;
    void vf44() override;
    void vf4C() override;
    bool vf54(u32) override;
    u32 vf5C() override;

    u8 _41C[0x420 - 0x41C];
};
