#pragma once

#include "types.h"

namespace sead {

template <typename T>
class SafeStringBase {
public:
    SafeStringBase()
        : stringTop(&sNullChar)
    { }

    SafeStringBase(const T* str)
        : stringTop(str)
    { }

    virtual ~SafeStringBase() { }
    virtual void assureTerminationImpl_() const { }

    inline const T* cstr() const {
        assureTerminationImpl_();
        return stringTop;
    }

    inline const SafeStringBase<T> getPart(s32 at) const {
        s32 len = calcLength();
        if (at < 0 || at > len)
            return SafeStringBase<T>::sEmptyString;

        return SafeStringBase<T>(stringTop + at);
    }

    inline const T& unsafeAt_(s32 idx) const {
        return stringTop[idx];
    }

    inline s32 calcLength() const;
    inline bool isEqual(const SafeStringBase<T>& str) const;
    inline s32 comparen(const SafeStringBase<T>& str, s32 n) const;
    inline s32 findIndex(const SafeStringBase<T>& str) const;

    static const T sNullChar;
    static const T sLineBreakChar;
    static const SafeStringBase sEmptyString;
    static const s32 sMaximumLength = 0x40000;

    const T* stringTop; // 0
};

typedef SafeStringBase<char> SafeString;

static_assert(sizeof(SafeString) == 0x8, "sead::SafeStringBase<T> size mismatch");

template <typename T>
class BufferedSafeStringBase : public SafeStringBase<T> {
public:
    BufferedSafeStringBase(T* buffer, s32 size)
        : SafeStringBase<T>(buffer)
        , bufferSize(size)
    {
        if (size <= 0)
        {
            //SEAD_ASSERT_MSG(false, "Invalied buffer size(%d).\n", size);
            stringTop = nullptr;
            bufferSize = 0;
            return;
        }

        assureTerminationImpl_();
    }

    BufferedSafeStringBase(BufferedSafeStringBase<T>* original, s32 pos)
        : SafeStringBase<T>(original->cstr())
        , bufferSize(0)
    {
        //SEAD_ASSERT_MSG(original, "original string must not be nullptr.");

        if (pos >= original->getBufferSize() || pos < 0)
        {
            //SEAD_ASSERT_MSG(false, "pos(%d) out of bounds[0,%d)", pos, original->getBufferSize());
            stringTop = nullptr;
            bufferSize = 0;
            return;
        }

        stringTop = original->stringTop + pos;
        bufferSize = original->getBufferSize() - pos;
        assureTerminationImpl_();
    }

private:
    BufferedSafeStringBase(const BufferedSafeStringBase<T>&);
    BufferedSafeStringBase<T>& operator=(const BufferedSafeStringBase<T>&);

public:
    virtual ~BufferedSafeStringBase()
    { }

    inline const T& operator[](s32 idx) const;

    s32 getBufferSize() const {
        return bufferSize;
    }

    inline s32 copy(const SafeStringBase<T>& rhs, s32 size = -1);

    inline void clear() {
        getMutableStringTop_()[0] = 0;
    }

    T* getBuffer() {
        assureTerminationImpl_();
        return getMutableStringTop_();
    }

private:
    T* getMutableStringTop_() {
        return const_cast<T*>(stringTop);
    }

protected:
    void assureTerminationImpl_() const override {
        BufferedSafeStringBase<T>* mutablePtr = const_cast<BufferedSafeStringBase<T>*>(this);
        mutablePtr->getMutableStringTop_()[getBufferSize() - 1] = 0;
    }

private:
    s32 bufferSize;
};

typedef BufferedSafeStringBase<char> BufferedSafeString;

static_assert(sizeof(BufferedSafeString) == 0xC, "sead::BufferedSafeStringBase<T> size mismatch");

template <typename T, s32 N>
class FixedSafeStringBase : public BufferedSafeStringBase<T> {
public:
    FixedSafeStringBase()
        : BufferedSafeStringBase<T>(buffer, N)
    {
        clear();
    }

    explicit FixedSafeStringBase(const SafeStringBase<T>& rhs)
        : BufferedSafeStringBase<T>(buffer, N)
    {
        copy(rhs);
    }

    FixedSafeStringBase(const FixedSafeStringBase<T, N>& rhs)
        : BufferedSafeStringBase<T>(buffer, N)
    {
        copy(rhs);
    }

    virtual ~FixedSafeStringBase()
    { }

    FixedSafeStringBase<T, N>& operator=(const FixedSafeStringBase<T, N>& rhs) {
        copy(rhs);
        return *this;
    }

    FixedSafeStringBase<T, N>& operator=(const SafeStringBase<T>& rhs) {
        copy(rhs);
        return *this;
    }

private:
    T buffer[N];
};

template <s32 N>
class FixedSafeString : public FixedSafeStringBase<char, N> {
public:
    FixedSafeString()
        : FixedSafeStringBase<char, N>()
    { }

    explicit FixedSafeString(const SafeString& rhs)
        : FixedSafeStringBase<char, N>(rhs)
    { }

    // Nintendo did not implement this
    //
    //FixedSafeString(const FixedSafeString<N>& rhs)
    //    : FixedSafeStringBase<char, N>(rhs)
    //{ }

    FixedSafeString<N>& operator=(const FixedSafeString<N>& rhs) {
        this->copy(rhs);
        return *this;
    }

    FixedSafeString<N>& operator=(const SafeString& rhs) {
        copy(rhs);
        return *this;
    }
};

}
