#pragma once

namespace nw { namespace ut { namespace internal {

class RuntimeTypeInfo {
public:
    RuntimeTypeInfo(const RuntimeTypeInfo* parent)
        : parentRTTI(parent)
    { }

    bool IsDerivedFrom(const RuntimeTypeInfo* rtti) const {
        for (const RuntimeTypeInfo* current = this; current; current = current->parentRTTI) {
            if (current == rtti)
                return true;
        }

        return false;
    }

    const RuntimeTypeInfo* parentRTTI;
};

} } }

#define NW_RTTI_BASE(CLASS) \
    public: \
        static const nw::ut::internal::RuntimeTypeInfo RTTI; \
        static const nw::ut::internal::RuntimeTypeInfo* GetRuntimeTypeInfoStatic() { \
            return &RTTI; \
        } \
        virtual const nw::ut::internal::RuntimeTypeInfo* GetRuntimeTypeInfo() const

#define NW_RTTI_OVERRIDE(CLASS, BASE) \
    public: \
        static const nw::ut::internal::RuntimeTypeInfo RTTI; \
        static const nw::ut::internal::RuntimeTypeInfo* GetRuntimeTypeInfoStatic() { \
            return &RTTI; \
        } \
        const nw::ut::internal::RuntimeTypeInfo* GetRuntimeTypeInfo() const override
