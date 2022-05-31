#pragma once

#include "types.h"

namespace sead {

class ListNode {
public:
    forceinline ListNode()
        : prev(nullptr)
        , next(nullptr)
    { }

    void insertFront_(ListNode* node);
    void erase_();

    ListNode* prev;
    ListNode* next;
};

class ListImpl {
public:
    forceinline ListImpl()
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

    void erase(ListNode* n) {
        n->erase_();
        count -= 1;
    }

    ListNode startEnd;
    s32 count;
};

template <typename T>
class TList : public ListImpl {
public:
    forceinline TList()
        : ListImpl()
    { }

    class iterator {
    public:
        iterator(TListNode<T>* ptr)
            : ptr(ptr) {
        }

        iterator& operator++() {
            ptr = static_cast<TListNode<T>*>(ptr->next);
            return *this;
        }

        iterator operator++(s32) {
            const iterator it(*this);
            (void)++*this;
            return it;
        }

        iterator& operator--() {
            ptr = static_cast<TListNode<T>*>(ptr->prev);
            return *this;
        }

        iterator operator--(s32) {
            const iterator it(*this);
            (void)--*this;
            return it;
        }

        friend bool operator==(iterator it1, iterator it2) {
            return it1.ptr == it2.ptr;
        }

        friend bool operator!=(iterator it1, iterator it2) {
            return !(it1 == it2);
        }

        TListNode<T>* ptr;
    };

    iterator begin() const {
        return iterator(static_cast<TListNode<T>*>(startEnd.next));
    }

    iterator end() const {
        return iterator(static_cast<TListNode<T>*>(const_cast<ListNode*>(&startEnd)));
    }

    void pushBack(TListNode<T>* obj) {
        obj->erase();
        obj->list = this;
        ListImpl::pushBack(obj);
    }

    void erase(TListNode<T>* obj) {
        obj->list = nullptr;
        ListImpl::erase(obj);
    }
};

template <typename T>
class TListNode : public ListNode {
public:
    forceinline TListNode()
        : ListNode()
        , data(nullptr)
        , list(nullptr)
    { }

    forceinline TListNode(T data)
        : ListNode()
        , data(data)
        , list(nullptr)
    { }

    void erase() {
        TList<T>* list = this->list;
        if (list != nullptr)
            list->erase(this);
    }

    T data;
    TList<T>* list;
};

template <typename T>
class OffsetList : public ListImpl {
public:
    forceinline OffsetList()
        : ListImpl()
        , offset(-1)
    { }

    void pushBack(T* item) {
        ListImpl::pushBack(objToListNode(item));
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
            ListNode* node = static_cast<ListNode*>(static_cast<void*>(ptr) + offset)->next;
            ptr = static_cast<T*>(static_cast<void*>(node) + -offset);
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

    ListNode* objToListNode(T* obj) const {
        return static_cast<ListNode*>(static_cast<void*>(obj) + offset);
    }

    const ListNode* objToListNode(const T* obj) const {
        return static_cast<const ListNode*>(static_cast<const void*>(obj) + offset);
    }

    T* listNodeToObj(ListNode* node) const {
        return static_cast<T*>(static_cast<void*>(node) + -offset);
    }

    const T* listNodeToObj(const ListNode* node) const {
        return static_cast<const T*>(static_cast<const void*>(node) + -offset);
    }

    s32 offset;
};

}
