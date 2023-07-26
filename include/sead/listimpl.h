#pragma once

#include "types.h"

namespace sead {

class ListNode {
public:
    ListNode()
        : prev(nullptr)
        , next(nullptr)
    { }

    void insertFront_(ListNode* node);
    void insertBack_(ListNode* node);
    void erase_();

    ListNode* prev;
    ListNode* next;
};
static_assert(sizeof(ListNode) == 0x8);

class ListImpl {
public:
    ListImpl()
        : startEnd()
        , count(0)
    {
        startEnd.next = &startEnd;
        startEnd.prev = &startEnd;
    }

    void pushBack(ListNode* n) {
        startEnd.insertFront_(n);
        count += 1;
    }

    void pushFront(ListNode* n)
    {
        startEnd.insertBack_(n);
        count += 1;
    }

    void erase(ListNode* n) {
        n->erase_();
        count -= 1;
    }

    ListNode* front() const { return count > 0 ? startEnd.next : nullptr; }
    ListNode* back() const { return count > 0 ? startEnd.prev : nullptr; }

    ListNode startEnd;
    s32 count;
};
static_assert(sizeof(ListImpl) == 0xC);

}
