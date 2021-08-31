#pragma once

#include <types.h>

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
        iterator(T* const* inPptr)
            : pptr(inPptr)
        { }

        bool operator==(const iterator& other) const {
            return this->pptr == other.pptr;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

        iterator& operator++() {
            ++this->pptr;
            return *this;
        }

        T& operator*() const {
            return **this->pptr;
        }

        T* operator->() const {
            return *this->pptr;
        }

        T* const* pptr;
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

    u8 work[N*sizeof(void*)];
};

}
