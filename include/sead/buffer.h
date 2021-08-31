#pragma once

#include <types.h>

namespace sead {

template <typename T>
class Buffer {
public:
    Buffer()
        : size(0)
        , buffer(NULL)
    { }

    void setBuffer(s32 size, T* bufferptr) {
        if (size > 0 && bufferptr) {
            this->size = size;
            this->buffer = bufferptr;
        }
    }

    T* unsafeGet(s32 index) {
        return &this->buffer[index];
    }

    const T* unsafeGet(s32 index) const {
        return &this->buffer[index];
    }

    T& operator[] (s32 index) {
        return *unsafeGet(index);
    }

    const T& operator[] (s32 index) const {
        return *unsafeGet(index);
    }

    s32 size;
    T* buffer;
};

}
