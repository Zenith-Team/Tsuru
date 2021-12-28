#pragma once

#include "sead/idisposer.h"
#include "sead/inamable.h"
#include "sead/messagequeue.h"
#include "dynlibs/os/types.h"

namespace sead {

class Thread : public IDisposer, public INamable {
public:
    Thread(sead::Heap* heap, OSThread* thread);
    Thread(const sead::SafeString& name, sead::Heap* heap, s32 priority, sead::MessageQueue::BlockType blockType, s32 quitMessage, s32 stackSize, s32 messageQueueSize);
    virtual ~Thread();

    virtual void destroy();
    virtual bool sendMessage(u32 element, MessageQueue::BlockType blockType);
    virtual s32 recvMessage(MessageQueue::BlockType blockType);
    virtual bool start();
    virtual void quit(bool);
    virtual void waitDone();
    virtual void quitAndDestroySingleThread(bool isJam);
    virtual void quitAndWatDoneSingleThread();

    u8 _18[0x90 - 0x18];
};

static_assert(sizeof(Thread) == 0x90, "sead::Thread size mismatch");

class DelegateThread : public Thread {
public:
    // TODO: Ctor

    virtual ~DelegateThread();

    void quitAndDestroySingleThread(bool isJam) override;

    u8 delegate[4];
};

static_assert(sizeof(DelegateThread) == 0x94, "sead::DelegateThread size mismatch");

}
