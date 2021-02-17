#pragma once

#include "types.h"

namespace sead {

class PtrArrayImpl
{
public:
    forceinline PtrArrayImpl(s32 ptrNumMax, void* buf)
        : mPtrNum(0)
        , mPtrNumMax(0)
        , mPtrs(NULL)
    {
        setBuffer(ptrNumMax, buf);
    }

    void setBuffer(s32 ptrNumMax, void* buf);

    s32 mPtrNum;
    s32 mPtrNumMax;
    void** mPtrs;
};

template <typename T>
class PtrArray : public PtrArrayImpl
{
public:
    forceinline PtrArray(s32 ptrNumMax, T** buf)
        : PtrArrayImpl(ptrNumMax, buf)
    {
    }

    class iterator
    {
    public:
        iterator(T* const* pptr)
            : mPPtr(pptr)
        {
        }

        bool operator==(const iterator& other) const
        {
            return mPPtr == other.mPPtr;
        }

        bool operator!=(const iterator& other) const
        {
            return !(*this == other);
        }

        iterator& operator++()
        {
            ++mPPtr;
            return *this;
        }

        T& operator*() const
        {
            return **mPPtr;
        }

        T* operator->() const
        {
            return *mPPtr;
        }

        T* const* mPPtr;
    };

    iterator begin() const
    {
        return iterator(reinterpret_cast<T**>(mPtrs));
    }

    iterator end() const
    {
        return iterator(reinterpret_cast<T**>(mPtrs) + mPtrNum);
    }
};

template <typename T, s32 N>
class FixedPtrArray : public PtrArray<T>
{
public:
    forceinline FixedPtrArray()
        : PtrArray<T>(N, reinterpret_cast<T**>(mWork))
    {
    }

    u8 mWork[N*sizeof(void*)];
};

}
