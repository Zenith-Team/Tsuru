#pragma once

#include "agl/lyr/layer.h"

class LayerAgl : public agl::lyr::Layer {
    SEAD_RTTI_OVERRIDE(LayerAgl, agl::lyr::Layer)

public:
    class Node {
        SEAD_RTTI_BASE(Node);

    public:
        virtual void calc() = 0;
    };

public:
    LayerAgl();
    virtual ~LayerAgl();

    void doInitialize(sead::Heap* heap) override;
    void vf3C() override;
    void preDrawImpl(const agl::lyr::RenderInfo& renderInfo) const override;
    void postDrawImpl(const agl::lyr::RenderInfo& renderInfo) const override;
    u32 vf54() override;
    u32 vf5C() override;

    u8 _41C[0x420 - 0x41C];
};
