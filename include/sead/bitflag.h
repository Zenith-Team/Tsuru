#pragma once

#include "types.h"

namespace sead {

template <typename T>
class BitFlag {
public:
    forceinline BitFlag()
        : bits(0)
    { }

    forceinline BitFlag(T t)
        : bits(t)
    { }

    void setDirect(T bitsV) { bits = bitsV; }
    T getDirect() const { return bits; }
    T* getPtr() { return &bits; }
    const T* getPtr() const { return &bits; }
    size_t getByteSize() const { return sizeof(T); }

    T getMask(T mask) const { return this->bits & mask; }
    static T makeMask(s32 bit) { return T(1) << bit; }

    bool isOn(T mask) const { return (this->bits & mask) != 0; }
    bool isOff(T mask) const { return !this->isOn(mask); }

    bool isOnBit(s32 bit) const { return this->isOn(makeMask(bit)); }
    bool isOffBit(s32 bit) const { return this->isOff(makeMask(bit)); }

    void set(T mask) { this->bits |= mask; }
    void reset(T mask) { this->bits &= ~mask; }
    void toggle(T mask) { this->bits ^= mask; }
    void change(T mask, bool b) { b ? set(mask) : reset(mask); }

    void setBit(s32 bit) { this->set(makeMask(bit)); }
    void resetBit(s32 bit) { this->reset(makeMask(bit)); }
    void changeBit(s32 bit, bool b) { this->change(makeMask(bit), b); }
    void toggleBit(s32 bit) { this->toggle(makeMask(bit)); }

    void makeAllZero() { this->bits = 0; }
    void makeAllOne() { this->bits = -1; }

    bool operator==(const BitFlag<T>& rhs) const { return this->bits == rhs.bits; }
    bool operator!=(const BitFlag<T>& rhs) const { return this->bits != rhs.bits; }

    T bits;
};

typedef BitFlag<u8> BitFlag8;
typedef BitFlag<u16> BitFlag16;
typedef BitFlag<u32> BitFlag32;
typedef BitFlag<u64> BitFlag64;

}
