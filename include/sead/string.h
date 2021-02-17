#pragma once

#include <stdarg.h>

namespace sead {

template <typename T>
class SafeStringBase
{
public:
    SafeStringBase() : mStringTop(&cNullChar) { }
    SafeStringBase(const T* str) : mStringTop(str) { }
    virtual ~SafeStringBase() { }

    virtual void assureTerminationImpl_() const { }

    inline const T* cstr() const
    {
        assureTerminationImpl_();
        return mStringTop;
    }

    inline const SafeStringBase<T> getPart(s32 at) const
    {
        s32 len = calcLength();
        if ( at < 0 || at > len )
            return SafeStringBase<T>::cEmptyString;

        return SafeStringBase<T>(mStringTop + at);
    }

    inline const T& unsafeAt_(s32 idx) const
    {
        return mStringTop[idx];
    }

    inline s32 calcLength() const;
    inline bool isEqual(const SafeStringBase<T>& str) const;
    inline s32 comparen(const SafeStringBase<T>& str, s32 n) const;
    inline s32 findIndex(const SafeStringBase<T>& str) const;

    static const T cNullChar;
    static const T cLineBreakChar;
    static const SafeStringBase cEmptyString;
    static const s32 cMaximumLength = 0x40000;

    const T* mStringTop;
};

template <>
extern const char SafeStringBase<char>::cNullChar;

template <>
extern const char SafeStringBase<char>::cLineBreakChar;

template <>
extern const SafeStringBase<char> SafeStringBase<char>::cEmptyString;

template <typename T>
class BufferedSafeStringBase : public SafeStringBase<T>
{
public:
    forceinline BufferedSafeStringBase(T* buffer, s32 size)
        : SafeStringBase<T>(buffer)
    {
        mBufferSize = size;
        assureTerminationImpl_();
    }

    virtual ~BufferedSafeStringBase() { }

    virtual void assureTerminationImpl_() const
    {
        BufferedSafeStringBase<T>* mutableSafeString = const_cast<BufferedSafeStringBase<T>*>(this);
        mutableSafeString->getMutableStringTop_()[mBufferSize - 1] = mutableSafeString->cNullChar;
    }

    s32 format(const T* formatStr, ...);
    s32 formatV(const T* formatStr, va_list args);
    s32 appendWithFormat(const T* formatStr, ...);
    s32 appendWithFormatV(const T* formatStr, va_list args);

    static s32 formatImpl_(T* s, s32 n, const T* formatStr, va_list args);

    inline T* getMutableStringTop_()
    {
        return const_cast<T*>(mStringTop);
    }

    inline void clear()
    {
        getMutableStringTop_()[0] = this->cNullChar;
    }

    inline s32 copy(const SafeStringBase<T>& src, s32 copyLength=-1);
    inline s32 copyAt(s32 at, const SafeStringBase<T>& src, s32 copyLength=-1);
    inline s32 trim(s32 trimLength);

    s32 mBufferSize;
};

template <typename T, s32 L>
class FixedSafeStringBase : public BufferedSafeStringBase<T>
{
public:
    FixedSafeStringBase()
        : BufferedSafeStringBase<T>(mBuffer, L)
    {
        clear();
    }

    explicit FixedSafeStringBase(const SafeStringBase<T>& str)
        : BufferedSafeStringBase<T>(mBuffer, L)
    {
        copy(str);
    }

    virtual ~FixedSafeStringBase() { }

    T mBuffer[L];
};

typedef SafeStringBase<char> SafeString;
typedef BufferedSafeStringBase<char> BufferedSafeString;

template <>
s32 BufferedSafeStringBase<char>::format(const char* formatStr, ...);
template <>
s32 BufferedSafeStringBase<char>::formatV(const char* formatStr, va_list args);
template <>
s32 BufferedSafeStringBase<char>::appendWithFormat(const char* formatStr, ...);
template <>
s32 BufferedSafeStringBase<char>::appendWithFormatV(const char* formatStr, va_list args);

template <s32 L>
class FixedSafeString : public FixedSafeStringBase<char, L>
{
public:
    FixedSafeString()
        : FixedSafeStringBase<char, L>()
    {
    }

    explicit FixedSafeString(const SafeString& str)
        : FixedSafeStringBase<char, L>(str)
    {
    }
};

template <s32 L>
class FormatFixedSafeString : public FixedSafeString<L>
{
public:
    FormatFixedSafeString(const char* str, ...)
        : FixedSafeString<L>()
    {
        va_list args;
        va_start(args, str);
        (void)formatV(str, args);
        va_end(args);
    }

    virtual ~FormatFixedSafeString() { }
};

}
