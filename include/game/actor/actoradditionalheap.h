#pragma once

#include "heap/seadHeap.h"

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
