#pragma once

#include <cstddef>
#include "preprocessor.h"

// Workarounds to meet newer standards

#ifndef _
    #define ASM_BEGIN #pragma asm
    #define ASM_END #pragma endasm
    #define ASM_FUNC(ret, name, ...) asm ret name(__VA_ARGS__)
    #define override
    #define static_assert(condition, ...) typedef int TOKENPASTE2(static_assert_, __LINE__)[(condition) ? 1 : -1]
    #define nullptr NULL
#else // intellisense
    #define ASM_BEGIN __asm {
    #define ASM_END }
    #define ASM_FUNC(ret, name, ...) __asm
    #define static_assert(x, ...)
    #define __attribute__(...)
#endif

#define GEN_LAMBDA_BODY(...) { __VA_ARGS__ } }
#define CAPTURE_LAMBDA_ARGS(...) (__VA_ARGS__) GEN_LAMBDA_BODY
#define $(ret) struct { ret operator() CAPTURE_LAMBDA_ARGS

#define PRAGMA(x) _Pragma(#x)
#ifndef forceinline
    #define forceinline __attribute__((always_inline))
#endif

#define ENUM_CLASS(name, ...)              \
    class name {virtual void This_error_means_you_forgot_to_write___type___in_an_object_instanciation()=0;public: \
        enum __type__ { __VA_ARGS__ };     \
    }

// Primitive type shortcuts

typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
typedef unsigned long long  u64;

typedef signed char         s8;
typedef signed short        s16;
typedef signed int          s32;
typedef signed long long    s64;

typedef float               f32;
typedef double              f64;

typedef unsigned int     size_t;
typedef signed int      ssize_t;

typedef unsigned int  uintptr_t;
typedef signed int     intptr_t;

typedef void       (*funcPtr)();

typedef wchar_t          char16;
typedef int                BOOL;

// Decl hack

#define SEAD_RTTI_BASE_DECL(CLASS)                                                                          \
    public:                                                                                                 \
        static const sead::RuntimeTypeInfo::Root RTTI;                                                      \
        static const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfoStatic() {                         \
            return &RTTI;                                                                                   \
        }                                                                                                   \
        virtual bool checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface* typeInfo) const;   \
        virtual const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const

#define SEAD_RTTI_OVERRIDE_DECL(CLASS, BASE)                                                                \
    public:                                                                                                 \
        static const sead::RuntimeTypeInfo::Derive<BASE> RTTI;                                              \
        static const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfoStatic() {                         \
            return &RTTI;                                                                                   \
        }                                                                                                   \
        bool checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface* typeInfo) const override;  \
        const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const override
