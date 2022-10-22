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
private:
    typedef s32 (*CompareCallback)(const T*, const T*);

public:
    TList()
        : ListImpl()
    { }

    void pushBack(TListNode<T>* obj) {
        obj->erase();
        obj->list = this;
        ListImpl::pushBack(obj);
    }

    void pushFront(TListNode<T>* obj);
    TListNode<T>* popBack();
    TListNode<T>* popFront();
    void insertBefore(TListNode<T>* basis, TListNode<T>* obj);
    void insertAfter(TListNode<T>* basis, TListNode<T>* obj);

    void erase(TListNode<T>* obj) {
        obj->list = NULL;
        ListImpl::erase(obj);
    }

    TListNode<T>* front() const;
    TListNode<T>* back() const;
    TListNode<T>* prev(const TListNode<T>* obj) const;
    TListNode<T>* next(const TListNode<T>* obj) const;
    TListNode<T>* nth(s32 index) const;
    s32 indexOf(const TListNode<T>* obj) const;
    bool isNodeLinked(const TListNode<T>* obj) const;
    void swap(TListNode<T>* obj1, TListNode<T>* obj2);
    void moveAfter(TListNode<T>* basis, TListNode<T>* obj);
    void moveBefore(TListNode<T>* basis, TListNode<T>* obj);
    void clear();
    void unsafeClear();
    void sort();
    void sort(CompareCallback cmp);
    void mergeSort();
    void mergeSort(CompareCallback cmp);
    TListNode<T>* find(const T* obj) const;
    TListNode<T>* find(const T* obj, CompareCallback cmp) const;
    void uniq();
    void uniq(CompareCallback cmp);

public:
    class iterator {
    public:
        iterator(TListNode<T>* ptr)
            : ptr(ptr)
        { }

        iterator& operator++() {
            this->ptr = static_cast<TListNode<T>*>(this->ptr->next());
            return *this;
        }

    public:
        T& operator*() const {
            return this->ptr->mData;
        }

        T* operator->() const {
            return &this->ptr->mData;
        }

        friend bool operator==(const iterator& it1, const iterator& it2) {
            return it1.this->ptr == it2.this->ptr;
        }

        friend bool operator!=(const iterator& it1, const iterator& it2) {
            return !(it1 == it2);
        }

    protected:
        TListNode<T>* ptr;
    };

    class constIterator { };
    class robustIterator { };
    class reverseIterator { };
    class reverseConstIterator { };
    class reverseRobustIterator { };

public:
    iterator begin() const {
        return iterator(static_cast<TListNode<T>*>(mStartEnd.next()));
    }

    iterator end() const {
        return iterator(static_cast<TListNode<T>*>(const_cast<ListNode*>(&mStartEnd)));
    }

    iterator toIterator(TListNode<T>*) const;
    constIterator constBegin() const;
    constIterator constEnd() const;
    constIterator toConstIterator(const TListNode<T>*) const;
    robustIterator robustBegin() const;
    robustIterator robustEnd() const;
    robustIterator toRobustIterator(TListNode<T>*) const;
    reverseIterator reverseBegin() const;
    reverseIterator reverseEnd() const;
    reverseIterator toReverseIterator(TListNode<T>*) const;
    reverseConstIterator reverseConstBegin() const;
    reverseConstIterator reverseConstEnd() const;
    reverseConstIterator toReverseConstIterator(const TListNode<T>*) const;
    reverseRobustIterator reverseRobustBegin() const;
    reverseRobustIterator reverseRobustEnd() const;
    reverseRobustIterator toReverseRobustIterator(TListNode<T>*) const;

protected:
    static s32 compareT(const T*, const T*);
};

template <typename T>
class TListNode : public ListNode {
public:
    TListNode()
        : ListNode()
        , data(NULL)
        , list(NULL)
    { }

    TListNode(T data)
        : ListNode()
        , data(data)
        , list(NULL)
    { }

    void insertBack(TListNode<T>* n);
    void insertFront(TListNode<T>* n);

    void erase() {
        TList<T>* list = list;
        if (list != NULL)
            list->erase(this);
    }

    T data;
    TList<T>* list;

    friend class TList<T>;
};

static_assert(sizeof(TListNode<int*>) == 0x10, "sead::TListNode<T> size mismatch");

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
