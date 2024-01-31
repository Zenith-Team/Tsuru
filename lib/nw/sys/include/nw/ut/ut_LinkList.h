#pragma once

#include "types.h"

namespace nw { namespace ut {

struct LinkListNode {
    LinkListNode* next;
    LinkListNode* prev;
};

namespace internal {

class LinkListImpl {
public:
    u32 size;
    LinkListNode baseNode;
};

}

} }
