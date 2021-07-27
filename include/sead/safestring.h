#pragma once

namespace sead {

template <typename T>
class SafeStringBase {
public:
    SafeStringBase()
        : mStringTop(&cNullChar)
    { }

    SafeStringBase(const T* str)
        : mStringTop(str)
    { }

    virtual ~SafeStringBase() { }
    virtual void assureTerminationImpl_() const { }

    inline const T* cstr() const {
        assureTerminationImpl_();
        return mStringTop;
    }

    inline const SafeStringBase<T> getPart(s32 at) const {
        s32 len = calcLength();
        if (at < 0 || at > len)
            return SafeStringBase<T>::cEmptyString;
        
        return SafeStringBase<T>(mStringTop + at);
    }

    inline const T& unsafeAt_(s32 idx) const {
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

    const T* mStringTop; // _4
};

typedef SafeStringBase<char> SafeString;

}