#pragma once

#include <types.h>

template <typename T, u32 N>
class MiniPointerList { // A mini pointer array with convenience functions
public:
    MiniPointerList()
        : data()
    { }

    // Appends given data to the first empty member
    // @param data Data to be entered into the array
    void append(const T& data) {
        for (u32 i = 0; i < N; i++) {
            if (this->data[i] != nullptr)
                continue;
            else
                this->data[i] = data; return;
        }
    }

    // @return The number of filled cells in the array
    u32 count() {
        u32 num = 0;
        for (u32 i = 0; i < N; i++) {
            if (this->data[i] != nullptr)
                num++;
        }

        return num;
    }

    // Clears the array
    void clear() {
        for (u32 i = 0; i < N; i++) {
            this->data[i] = nullptr;
        }
    }

    // Gets the value from the array at index
    // @param index Array index to get from
    T& operator[](u32 index) {
        return this->data[index];
    }

    T data[N];
};
