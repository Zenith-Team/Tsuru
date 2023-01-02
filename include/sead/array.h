#pragma once

#include "types.h"

namespace sead {

template <typename T, s32 N>
class SafeArray {
public:
    T& operator[](s32 i) {
        if (static_cast<u32>(i) < static_cast<u32>(N)) {
            return this->buffer[i];
        } else {
            return this->buffer[0];
        }
    }

    const T& operator[](s32 i) const {
        if (static_cast<u32>(i) < static_cast<u32>(N)) {
            return this->buffer[i];
        } else {
            return this->buffer[0];
        }
    }

    T& front() { return this->buffer[0]; }
    const T& front() const { return this->buffer[0]; }

    T& back() { return this->buffer[N - 1]; }
    const T& back() const { return this->buffer[N - 1]; }

    u32 count() const { return N; }
    u32 size() const { return N * sizeof(T); }

    T* bufferPtr() { return this->buffer; }
    const T* bufferPtr() const { return this->buffer; }

    void fill(const T& value) {
        for (s32 i = 0; i < N; ++i) {
            this->buffer[i] = value;
        }
    }

public:
    class iterator {
    public:
        explicit iterator(T* buffer, s32 index = 0)
            : ptr(buffer + index)
            , start(buffer)
        { }

        bool operator==(const iterator& rhs) const { return this->ptr == rhs.ptr; }
        bool operator!=(const iterator& rhs) const { return this->ptr != rhs.ptr; }

        iterator& operator++() {
            this->ptr++;
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            this->ptr++;
            return tmp;
        }

        iterator& operator--() {
            this->ptr--;
            return *this;
        }

        iterator operator--(int) {
            iterator tmp = *this;
            this->ptr--;
            return tmp;
        }

        iterator operator*() const { return *this->ptr; }
        iterator operator->() const { return this->ptr; }

        s32 index() const { return ((uintptr_t)this->ptr - (uintptr_t)this->start) / sizeof(T); }

    private:
        T* ptr;
        T* start;
    };

    class constIterator {
    public:
        explicit constIterator(const T* buffer, s32 index = 0)
            : ptr(buffer + index)
            , start(buffer)
        { }

        bool operator==(const constIterator& rhs) const { return this->ptr == rhs.ptr; }
        bool operator!=(const constIterator& rhs) const { return this->ptr != rhs.ptr; }

        constIterator& operator++() {
            this->ptr++;
            return *this;
        }

        constIterator operator++(int) {
            constIterator tmp = *this;
            this->ptr++;
            return tmp;
        }

        constIterator& operator--() {
            this->ptr--;
            return *this;
        }

        constIterator operator--(int) {
            constIterator tmp = *this;
            this->ptr--;
            return tmp;
        }

        constIterator operator*() const { return *this->ptr; }
        constIterator operator->() const { return this->ptr; }

        s32 index() const { return ((uintptr_t)this->ptr - (uintptr_t)this->start) / sizeof(T); }

    private:
        const T* ptr;
        const T* start;
    };

public:
    iterator begin() { return iterator(this->buffer); }
    constIterator begin() const { return constIterator(this->buffer); }

    iterator end() { return iterator(this->buffer, N); }
    constIterator end() const { return constIterator(this->buffer, N); }

    constIterator cbegin() const { return constIterator(this->buffer); }
    constIterator cend() const { return constIterator(this->buffer, N); }

    T buffer[N];
};

}
