#pragma once

#include "sead/heap.h"

class ActorAdditionalHeap : public sead::IDisposer {
public:
    ActorAdditionalHeap()
        : sead::IDisposer()
        , heap(nullptr)
    { }

    ~ActorAdditionalHeap() {
        this->destroy();
    }

    void create();

private:
    void destroy();

public:
    sead::Heap* heap; // sead::FrameHeap*
};
