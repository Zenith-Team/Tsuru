#pragma once

#include "list.h"
#include "types.h"

namespace sead {

class Heap;

class IDisposer
{
public:
    IDisposer();
    virtual ~IDisposer();

private:
    Heap* mDisposerHeap;
    ListNode mListNode;
};

}
