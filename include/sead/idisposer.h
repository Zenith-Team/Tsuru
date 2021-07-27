#pragma once

#include "list.h"

namespace sead {

class Heap;

class IDisposer {
public:
    IDisposer();
    virtual ~IDisposer();

private:
    Heap* mDisposerHeap;
    ListNode mListNode;
};

}

#define SEAD_SINGLETON_DISPOSER(CLASS)                                        \
public:                                                                       \
    class SingletonDisposer_ : public sead::IDisposer {                       \
    public:                                                                   \
        SingletonDisposer_() : IDisposer() { }                                \
        virtual ~SingletonDisposer_() {                                       \
            if (this == sStaticDisposer) {                                    \
                sStaticDisposer = nullptr;                                    \
                CLASS::sInstance->~CLASS();                                   \
                CLASS::sInstance = nullptr;                                   \
            }                                                                 \
        }                                                                     \
                                                                              \
        static SingletonDisposer_* sStaticDisposer;                           \
    };                                                                        \
                                                                              \
    static CLASS* createInstance(sead::Heap* heap);                           \
    static void deleteInstance();                                             \
                                                                              \
    static CLASS* sInstance;                                                  \
                                                                              \
    u32 mSingletonDisposerBuf_[sizeof(SingletonDisposer_) / sizeof(u32)];

#define SEAD_CREATE_SINGLETON_INSTANCE(CLASS)                                                                    \
    CLASS* CLASS::createInstance(sead::Heap* heap) {                                                             \
        CLASS::SingletonDisposer_* staticDisposer = CLASS::SingletonDisposer_::sStaticDisposer;                  \
        CLASS* instance = CLASS::sInstance;                                                                      \
                                                                                                                 \
        if (!CLASS::sInstance) {                                                                                 \
            instance = reinterpret_cast<CLASS*>(new(heap, 4) u8[sizeof(CLASS)]);                                 \
            staticDisposer = reinterpret_cast<CLASS::SingletonDisposer_*>(instance->mSingletonDisposerBuf_);     \
                                                                                                                 \
            CLASS::SingletonDisposer_::sStaticDisposer = new (staticDisposer) SingletonDisposer_();              \
            CLASS::sInstance = new (instance) CLASS();                                                           \
        }                                                                                                        \
                                                                                                                 \
        return CLASS::sInstance;                                                                                 \
    }

#define SEAD_DELETE_SINGLETON_INSTANCE(CLASS)                                                       \
    void CLASS::deleteInstance() {                                                                  \
        CLASS::SingletonDisposer_* staticDisposer = CLASS::SingletonDisposer_::sStaticDisposer;     \
        if (CLASS::SingletonDisposer_::sStaticDisposer) {                                           \
            CLASS::SingletonDisposer_::sStaticDisposer = nullptr;                                   \
            staticDisposer->~SingletonDisposer_();                                                  \
                                                                                                    \
            if (CLASS::sInstance)                                                                   \
                delete CLASS::sInstance;                                                            \
                                                                                                    \
            CLASS::sInstance = nullptr;                                                             \
        }                                                                                           \
    }

#define SEAD_SINGLETON_DISPOSER_IMPL(CLASS)                                             \
    SEAD_CREATE_SINGLETON_INSTANCE(CLASS)                                               \
    SEAD_DELETE_SINGLETON_INSTANCE(CLASS)                                               \
    CLASS* CLASS::sInstance = nullptr;                                                  \
    CLASS::SingletonDisposer_* CLASS::SingletonDisposer_::sStaticDisposer = nullptr;
