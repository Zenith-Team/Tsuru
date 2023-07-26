#pragma once

#include "sead/listimpl.h"

namespace sead {

template <typename T>
class TList;

template <typename T>
class TListNode : public ListNode {
public:
    TListNode()
        : ListNode()
        , data(nullptr)
        , list(nullptr)
    { }

    TListNode(T dataV)
        : ListNode()
        , data(dataV)
        , list(nullptr)
    { }

    void insertBack(TListNode<T>* n);
    void insertFront(TListNode<T>* n);

    void erase() {
        if (this->list)
            this->list->erase(this);
    }

    T data;
    TList<T>* list;
};

static_assert(sizeof(TListNode<int*>) == 0x10, "sead::TListNode<T> size mismatch");

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
        obj->list = nullptr;
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
        iterator(TListNode<T>* ptrV)
            : ptr(ptrV)
        { }

        iterator& operator++() {
            this->ptr = static_cast<TListNode<T>*>(this->ptr->next);
            return *this;
        }

    public:
        T& operator*() const {
            return this->ptr->data;
        }

        T* operator->() const {
            return &this->ptr->data;
        }

        friend bool operator==(const iterator& it1, const iterator& it2) {
            return it1.ptr == it2.ptr;
        }

        friend bool operator!=(const iterator& it1, const iterator& it2) {
            return it1.ptr != it2.ptr;
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
        return iterator(static_cast<TListNode<T>*>(this->startEnd.next));
    }

    iterator end() const {
        return iterator(static_cast<TListNode<T>*>(const_cast<ListNode*>(&this->startEnd)));
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

}
