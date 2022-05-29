#pragma once

#include "types.h"

namespace sead { namespace RuntimeTypeInfo {

class Interface {
public:
    Interface() { }
    virtual bool isDerived(const Interface* typeInfo) const = 0;
};

class Root : public Interface {
public:
    Root() { }

    bool isDerived(const Interface* typeInfo) const override {
        return typeInfo == this;
    }
};

template <typename BaseType>
class Derive : public Interface {
public:
    Derive() { }

    bool isDerived(const Interface* typeInfo) const override {
        if (this == typeInfo)
            return true;

        const RuntimeTypeInfo::Interface* rootTypeInfo = BaseType::getRuntimeTypeInfoStatic();
        return rootTypeInfo->isDerived(typeInfo);
    }
};

}

// Checks if an object derives from another class
// @param obj Object to be evaluated
// @return Whether or not the object derives
template <typename DerivedType, typename Type>
inline bool IsDerivedFrom(const Type* obj) {
    const RuntimeTypeInfo::Interface* typeInfo = DerivedType::getRuntimeTypeInfoStatic();
    return obj != nullptr && obj->checkDerivedRuntimeTypeInfo(typeInfo);
}

// Casts between derived classes
// @param obj Object to be casted
// @return Casted object
template<typename DerivedType, typename Type>
inline DerivedType* DynamicCast(Type* obj) {
    if (IsDerivedFrom<DerivedType, Type>(obj))
        return static_cast<DerivedType*>(obj);

    return nullptr;
}

}

#define SEAD_RTTI_BASE(CLASS) \
    public: \
        static const sead::RuntimeTypeInfo::Root RTTI; \
        static const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfoStatic() {                          \
            return &RTTI;                                                                                    \
        }                                                                                                    \
        virtual bool checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface* typeInfo) const; \
        virtual const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const

#define SEAD_RTTI_BASE_IMPL(CLASS)                                                                           \
    public:                                                                                                  \
        static const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfoStatic() {                          \
            static const sead::RuntimeTypeInfo::Root typeInfo;                                               \
            return &typeInfo;                                                                                \
        }                                                                                                    \
                                                                                                             \
        virtual bool checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface* typeInfo) const {   \
            const sead::RuntimeTypeInfo::Interface* clsTypeInfo = CLASS::getRuntimeTypeInfoStatic();         \
            return typeInfo == clsTypeInfo;                                                                  \
        }                                                                                                    \
                                                                                                             \
        virtual const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const {                         \
            return getRuntimeTypeInfoStatic();                                                               \
        } ((void)0)

#define SEAD_RTTI_OVERRIDE(CLASS, BASE)                                                                     \
    public:                                                                                                 \
        static const sead::RuntimeTypeInfo::Derive<BASE> RTTI;                                             \
        static const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfoStatic() {                         \
            return &RTTI;                                                                                   \
        }                                                                                                   \
        bool checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface* typeInfo) const override;  \
        const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const override;

#define SEAD_RTTI_OVERRIDE_IMPL(CLASS, BASE)                                                                 \
    public:                                                                                                  \
        static const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfoStatic() {                          \
            static const sead::RuntimeTypeInfo::Derive<BASE> typeInfo;                                       \
            return &typeInfo;                                                                                \
        }                                                                                                    \
                                                                                                             \
        virtual bool checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface* typeInfo) const {   \
            const sead::RuntimeTypeInfo::Interface* clsTypeInfo = CLASS::getRuntimeTypeInfoStatic();         \
            if (typeInfo == clsTypeInfo)                                                                     \
                return true;                                                                                 \
                                                                                                             \
            return BASE::checkDerivedRuntimeTypeInfo(typeInfo);                                              \
        }                                                                                                    \
                                                                                                             \
        virtual const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const {                         \
            return getRuntimeTypeInfoStatic();                                                               \
        }
