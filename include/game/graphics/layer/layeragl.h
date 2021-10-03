#pragma once

#include <agl/lyr/layer.h>

class LayerAgl : public agl::lyr::Layer {
public:
    class Node {
        SEAD_RTTI_BASE(Node)

    public:
        virtual void Calc() = 0;
    };

public:
    LayerAgl();
    virtual ~LayerAgl();

    u8 _41C[0x420 - 0x41C];
};
