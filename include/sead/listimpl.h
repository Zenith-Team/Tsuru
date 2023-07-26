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

static_assert(sizeof(ListNode) == 0x8, "sead::ListNode size mismatch");

class ListImpl {
public:
    ListImpl()
        : startEnd()
        , count(0)
    {
        this->startEnd.next = &this->startEnd;
        this->startEnd.prev = &this->startEnd;
    }

    void pushBack(ListNode* n) {
        this->startEnd.insertFront_(n);
        this->count += 1;
    }

    void pushFront(ListNode* n) {
        this->startEnd.insertBack_(n);
        this->count += 1;
    }

    void erase(ListNode* n) {
        n->erase_();
        this->count -= 1;
    }

    ListNode* front() const { return this->count > 0 ? this->startEnd.next : nullptr; }
    ListNode* back() const { return this->count > 0 ? this->startEnd.prev : nullptr; }

    ListNode startEnd;
    s32 count;
};
static_assert(sizeof(ListImpl) == 0xC);

}
