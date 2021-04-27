#pragma once

#include "types.h"

template <class T>
struct List {
    u32 count;
    T* list;
};

namespace sead {

class ListNode {
public:
    forceinline ListNode()
        : mPrev(NULL)
        , mNext(NULL)
    { }

    void insertFront_(ListNode* node);
    void erase_();

    ListNode* mPrev;
    ListNode* mNext;
};

class ListImpl {
public:
    forceinline ListImpl()
        : mStartEnd(), mCount(0) {
        mStartEnd.mNext = &mStartEnd;
        mStartEnd.mPrev = &mStartEnd;
    }

    void pushBack(ListNode* n) {
        mStartEnd.insertFront_(n);
        mCount += 1;
    }

    void erase(ListNode* n) {
        n->erase_();
        mCount -= 1;
    }

    ListNode mStartEnd;
    s32 mCount;
};

template <typename T>
class TListNode;

template <typename T>
class TList : public ListImpl {
public:
    forceinline TList()
        : ListImpl()
    { }

    class iterator {
    public:
        iterator(TListNode<T>* ptr)
            : mPtr(ptr) {
        }

        iterator& operator++() {
            mPtr = static_cast<TListNode<T>*>(mPtr->mNext);
            return *this;
        }

        iterator operator++(int) {
            const iterator it(*this);
            (void)++*this;
            return it;
        }

        iterator& operator--() {
            mPtr = static_cast<TListNode<T>*>(mPtr->mPrev);
            return *this;
        }

        iterator operator--(int)
        {
            const iterator it(*this);
            (void)--*this;
            return it;
        }

        friend bool operator==(iterator it1, iterator it2) {
            return it1.mPtr == it2.mPtr;
        }

        friend bool operator!=(iterator it1, iterator it2) {
            return !(it1 == it2);
        }

        TListNode<T>* mPtr;
    };

    iterator begin() const {
        return iterator(static_cast<TListNode<T>*>(mStartEnd.mNext));
    }

    iterator end() const {
        return iterator(static_cast<TListNode<T>*>(const_cast<ListNode*>(&mStartEnd)));
    }

    void pushBack(TListNode<T>* obj) {
        obj->erase();
        obj->mList = this;
        ListImpl::pushBack(obj);
    }

    void erase(TListNode<T>* obj) {
        obj->mList = NULL;
        ListImpl::erase(obj);
    }
};

template <typename T>
class TListNode : public ListNode {
public:
    forceinline TListNode()
        : ListNode()
        , mData(NULL)
        , mList(NULL)
    { }

    forceinline TListNode(T data)
        : ListNode()
        , mData(data)
        , mList(NULL)
    { }

    void erase() {
        TList<T>* list = mList;
        if (list != NULL)
            list->erase(this);
    }

    T mData;
    TList<T>* mList;
};

template <typename T>
class OffsetList : public ListImpl {
public:
    forceinline OffsetList()
        : ListImpl(), mOffset(-1)
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
            : mPtr(ptr), mOffset(offset)
        { }

        bool operator==(const iterator& other) const {
            return mPtr == other.mPtr;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

        iterator& operator++() {
            ListNode* node = static_cast<ListNode*>(static_cast<void*>(mPtr) + mOffset)->mNext;
            mPtr = static_cast<T*>(static_cast<void*>(node) + -mOffset);
            return *this;
        }

        T& operator*() const {
            return *mPtr;
        }

        T* operator->() const {
            return mPtr;
        }

        T* mPtr;
        s32 mOffset;
    };

    iterator begin() const {
        return iterator(listNodeToObj(mStartEnd.mNext), mOffset);
    }

    iterator end() const {
        return iterator(listNodeToObj(const_cast<ListNode*>(&mStartEnd)), mOffset);
    }

    ListNode* objToListNode(T* obj) const {
        return static_cast<ListNode*>(static_cast<void*>(obj) + mOffset);
    }

    const ListNode* objToListNode(const T* obj) const {
        return static_cast<const ListNode*>(static_cast<const void*>(obj) + mOffset);
    }

    T* listNodeToObj(ListNode* node) const {
        return static_cast<T*>(static_cast<void*>(node) + -mOffset);
    }

    const T* listNodeToObj(const ListNode* node) const {
        return static_cast<const T*>(static_cast<const void*>(node) + -mOffset);
    }

    s32 mOffset;
};

}
