#pragma once

#include "types.h"
#include "dynlibs/os/types.h"

namespace sead {

class MessageQueue {
public:
    enum BlockType {
        BlockType_Block,
        BlockType_NoBlock
    };

    typedef s32 Element;

public:
    MessageQueue();
    ~MessageQueue();

    void allocate(s32 size, Heap* heap);
    void free();

    bool push(Element message, BlockType blockType);
    Element pop(BlockType blockType);
    Element peek(BlockType blockType) const;
    bool jam(Element message, BlockType blockType);

    static const Element cNullElement = 0;

    u32* buffer;
    OSMessageQueue messageQueueInner;
};
static_assert(sizeof(MessageQueue) == 0x40);

}
