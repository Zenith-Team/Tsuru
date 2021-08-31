#pragma once

#include <types.h>

namespace sead {

class ListNode {
public:
    forceinline ListNode()
        : prev(NULL)
        , next(NULL)
    { }

    void insertFront_(ListNode* node);
    void erase_();

    ListNode* prev;
    ListNode* next;
};

class ListImpl {
public:
    forceinline ListImpl()
        : startEnd(), count(0) {
            this->startEnd.next = &this->startEnd;
            this->startEnd.prev = &this->startEnd;
        }
    
    void pushBack(ListNode* n) {
        this->startEnd.insertFront_(n);
        this->count += 1;
    }

    void erase(ListNode* n) {
        n->erase_();
        this->count -= 1;
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
        iterator(TListNode<T>* inPtr)
            : ptr(inPtr) {
        }

        iterator& operator++() {
            this->ptr = static_cast<TListNode<T>*>(this->ptr->next);
            return *this;
        }

        iterator operator++(int) {
            const iterator it(*this);
            (void)++*this;
            return it;
        }

        iterator& operator--() {
            this->ptr = static_cast<TListNode<T>*>(this->ptr->prev);
            return *this;
        }

        iterator operator--(int) {
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
        obj->list = NULL;
        ListImpl::erase(obj);
    }
};

template <typename T>
class TListNode : public ListNode {
public:
    forceinline TListNode()
        : ListNode()
        , data(NULL)
        , list(NULL)
    { }

    forceinline TListNode(T data)
        : ListNode()
        , data(data)
        , list(NULL)
    { }

    void erase() {
        TList<T>* tempList = this->list;
        if (tempList != NULL)
            tempList->erase(this);
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
        iterator(T* inPtr, s32 inOffset)
            : ptr(inPtr)
            , offset(inOffset)
        { }

        bool operator==(const iterator& other) const {
            return this->ptr == other.ptr;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

        iterator& operator++() {
            ListNode* node = static_cast<ListNode*>(static_cast<void*>(this->ptr) + this->offset)->next;
            this->ptr = static_cast<T*>(static_cast<void*>(node) + -this->offset);
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
