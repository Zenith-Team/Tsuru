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

    bool isDerived(const Interface* typeInfo) const {
        return typeInfo == this;
    }
};

template <typename BaseType>
class Derive : public Interface {
public:
    Derive() { }

    bool isDerived(const Interface* typeInfo) const {
        if (this == typeInfo)
            return true;
        
        const RuntimeTypeInfo::Interface* rootTypeInfo = BaseType::getRuntimeTypeInfoStatic();
        return rootTypeInfo->isDerived(typeInfo);
    }
};

}

template <typename DerivedType, typename Type>
inline bool
IsDerivedFrom(const Type* obj) {
    const RuntimeTypeInfo::Interface* typeInfo = DerivedType::getRuntimeTypeInfoStatic();
    return obj != NULL && obj->checkDerivedRuntimeTypeInfo(typeInfo);
}

template<typename DerivedType, typename Type>
inline DerivedType*
DynamicCast(Type* obj) {
    if (IsDerivedFrom<DerivedType, Type>(obj))
        return static_cast<DerivedType*>(obj);

    return NULL;
}

}

#define SEAD_RTTI_BASE(CLASS)                                                                                \
    public:                                                                                                  \
        static const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfoStatic() {                          \
            static const sead::RuntimeTypeInfo::Root typeInfo;                                               \
            return &typeInfo;                                                                                \
        }                                                                                                    \
                                                                                                             \
        virtual bool checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface* typeInfo) const;    \
        virtual const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const;

#define SEAD_RTTI_OVERRIDE(CLASS, BASE)                                                                      \
    public:                                                                                                  \
        static const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfoStatic() {                          \
            static const sead::RuntimeTypeInfo::Derive<BASE> typeInfo;                                       \
            return &typeInfo;                                                                                \
        }                                                                                                    \
                                                                                                             \
        virtual bool checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface* typeInfo) const;    \
        virtual const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const;

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
