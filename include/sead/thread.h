#pragma once

#include "sead/idisposer.h"
#include "sead/inamable.h"
#include "sead/messagequeue.h"
#include "sead/tlist.h"
#include "dynlibs/os/types.h"

namespace sead {

class Thread : public IDisposer, public INamable {
public:
    enum State
    {
        State_Initialized = 0,
        State_Running,
        State_Quitting,
        State_Terminated,
        State_Released
    };

    typedef TListNode<Thread*> ListNode;
    typedef TList<Thread*> List;

private:
    Thread(sead::Heap* heap, OSThread* thread);

public:
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

    MessageQueue messageQueue;
    s32 stackSize;
    ListNode listNode;
    Heap* currentHeap;
    MessageQueue::BlockType blockType;
    s32 quitMsg;
    u32 id;
    State state;
    s32 coreNo;
    OSThread* threadInner;
    u8* stackTop;
    s32 priority;
};

static_assert(sizeof(Thread) == 0x90, "sead::Thread size mismatch");

class DelegateThread : public Thread {
public:
    DelegateThread(const SafeString& name, void* delegate, Heap* heap, s32 priority, MessageQueue::BlockType blockType, s32 quitMsg, s32 stackSize, s32 messageQueueSize);
    virtual ~DelegateThread();

    void quitAndDestroySingleThread(bool isJam) override;

    void* delegate;
};

static_assert(sizeof(DelegateThread) == 0x94, "sead::DelegateThread size mismatch");

}
