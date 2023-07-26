#pragma once

#include "sead/listimpl.h"

namespace sead {

template <typename T>
class OffsetList : public ListImpl {
public:
    OffsetList()
        : ListImpl()
        , offset(-1)
    { }

    void pushBack(T* item) {
        ListImpl::pushBack(objToListNode(item));
    }

    void pushFront(T* item) {
        ListImpl::pushFront(objToListNode(item));
    }

    void erase(T* item) {
        ListImpl::erase(objToListNode(item));
    }

    class iterator {
    public:
        iterator(T* ptr, s32 offset)
            : ptr(ptr)
            , offset(offset)
        { }

        bool operator==(const iterator& other) const {
            return this->ptr == other.ptr;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

        iterator& operator++() {
            ListNode* node = reinterpret_cast<ListNode*>((uintptr_t)this->ptr + this->offset)->next;
            this->ptr = reinterpret_cast<T*>((uintptr_t)node - this->offset);
            return *this;
        }

        T& operator*() const {
            return *this->ptr;
        }

        T* operator->() const {
            return this->ptr;
        }

        T* ptr;
        s32 offset;
    };

    iterator begin() const {
        return iterator(this->listNodeToObj(this->startEnd.next), this->offset);
    }

    iterator end() const {
        return iterator(this->listNodeToObj(const_cast<ListNode*>(&this->startEnd)), this->offset);
    }

protected:
    ListNode* objToListNode(const T* obj) const {
        return reinterpret_cast<ListNode*>((uintptr_t)obj + this->offset);
    }

    T* listNodeToObj(const ListNode* node) const {
        return reinterpret_cast<T*>((uintptr_t)node - this->offset);
    }

public:
    s32 offset;
};

static_assert(sizeof(OffsetList<int>) == 0x10, "sead::OffsetList size mismatch");

}
