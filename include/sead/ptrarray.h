#pragma once

#include "types.h"

namespace sead {

class PtrArrayImpl {
public:
    forceinline PtrArrayImpl(s32 ptrNumMax, void* buf)
        : ptrNum(0)
        , ptrNumMax(0)
        , ptrs(NULL)
    {
        setBuffer(ptrNumMax, buf);
    }

    void setBuffer(s32 ptrNumMax, void* buf);

    s32 ptrNum;
    s32 ptrNumMax;
    void** ptrs;
};

template <typename T>
class PtrArray : public PtrArrayImpl {
public:
    forceinline PtrArray(s32 ptrNumMax, T** buf)
        : PtrArrayImpl(ptrNumMax, buf)
    { }

    class iterator {
    public:
        iterator(T* const* pptr)
            : PPtr(pptr)
        { }

        bool operator==(const iterator& other) const {
            return PPtr == other.PPtr;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

        iterator& operator++() {
            ++PPtr;
            return *this;
        }

        T& operator*() const {
            return **PPtr;
        }

        T* operator->() const {
            return *PPtr;
        }

        T* const* PPtr;
    };

    iterator begin() const {
        return iterator(reinterpret_cast<T**>(ptrs));
    }

    iterator end() const {
        return iterator(reinterpret_cast<T**>(ptrs) + ptrNum);
    }
};

template <typename T, s32 N>
class FixedPtrArray : public PtrArray<T> {
public:
    forceinline FixedPtrArray()
        : PtrArray<T>(N, reinterpret_cast<T**>(work))
    { }

    T& operator[](s32 index) {
        return *(reinterpret_cast<T**>(ptrs)[index]);
    }

    const T& operator[](s32 index) const {
        return *(reinterpret_cast<T**>(ptrs)[index]);
    }

    u8 work[N * sizeof(void*)];
};

}
