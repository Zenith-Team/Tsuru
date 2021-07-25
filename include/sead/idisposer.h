#pragma once

#include "list.h"

namespace sead {

class Heap;

class IDisposer {
public:
    IDisposer();
    virtual ~IDisposer();

private:
    Heap* mDisposerHeap;
    ListNode mListNode;
};

}


