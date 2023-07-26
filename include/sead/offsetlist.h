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
            return ptr == other.ptr;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

        iterator& operator++() {
            ListNode* node = reinterpret_cast<ListNode*>((uintptr_t)ptr + offset)->next;
            ptr = reinterpret_cast<T*>((uintptr_t)node - offset);
            return *this;
        }

        T& operator*() const {
            return *ptr;
        }

        T* operator->() const {
            return ptr;
        }

        T* ptr;
        s32 offset;
    };

    iterator begin() const {
        return iterator(listNodeToObj(startEnd.next), offset);
    }

    iterator end() const {
        return iterator(listNodeToObj(const_cast<ListNode*>(&startEnd)), offset);
    }

protected:
    ListNode* objToListNode(const T* obj) const
    {
        return reinterpret_cast<ListNode*>((uintptr_t)obj + offset);
    }

    T* listNodeToObj(const ListNode* node) const
    {
        return reinterpret_cast<T*>((uintptr_t)node - offset);
    }

public:
    s32 offset;
};
static_assert(sizeof(OffsetList<int>) == 0x10);

}
