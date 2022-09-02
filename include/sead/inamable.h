#pragma once

#include "sead/safestring.h"

namespace sead {

class INamable {
public:
    INamable()
        : INamableName()
    { }

    INamable(const char* str)
        : INamableName(str)
    { }

    INamable(const SafeString& str)
        : INamableName(str)
    { }

    ~INamable() { }

    void setName(const char* str) {
        INamableName = str;
    }

    void setName(const SafeString& str) {
        this->setName(str.cstr());
    }

    const SafeString& getName() const {
        return INamableName;
    }

    SafeString INamableName;
};

}
