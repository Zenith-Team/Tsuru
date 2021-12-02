#ifndef SEAD_FRAMEWORK_H_
#define SEAD_FRAMEWORK_H_

//#include "sead/framework/seadMethodTreeMgr.h"
#include "sead/framework/seadTaskBase.h"
//#include "sead/framework/seadTaskMgr.h"
//#include "gfx/seadFrameBuffer.h"
//#include "sead/heap/seadArena.h"
//#include "sead/heap/seadHeap.h"
#include "sead/hostio/seadHostIOMgr.h"
#include "sead/prim/seadDelegateEventSlot.h"
#include "sead/prim/seadRuntimeTypeInfo.h"
#include "sead/time/seadTickSpan.h"

namespace sead {

class Arena;

class FrameBuffer;
class Heap;
class LogicalFrameBuffer;
class MethodTreeMgr;
class TaskMgr;

class Framework
{
    SEAD_RTTI_BASE(Framework)

public:
    struct CreateSystemTaskArg
    {
        inline CreateSystemTaskArg();

        HostIOMgr::Parameter* hostio_parameter;
        TickSpan infloop_detection_span;
    };

    struct InitializeArg
    {
        InitializeArg();

        u32 heap_size;
        Arena* arena;
    };

    struct RunArg
    {
        RunArg();

        u32 prepare_stack_size;
        s32 prepare_priority;
    };

    enum ProcessPriority
    {
        cProcessPriority_Idle = 0,
        cProcessPriority_Normal = 1,
        cProcessPriority_High = 2,
        cProcessPriority_RealTime = 3
    };

public:
    Framework();
    virtual ~Framework();

    virtual void run(Heap*, const TaskBase::CreateArg&, const RunArg&);
    virtual void createSystemTasks(TaskBase*, const CreateSystemTaskArg&);
    virtual FrameBuffer* getMethodFrameBuffer(s32) const = 0;
    virtual LogicalFrameBuffer* getMethodLogicalFrameBuffer(s32) const;
    virtual bool setProcessPriority(ProcessPriority);
    virtual void reserveReset(void*);
    virtual void initRun_(Heap*);
    virtual void runImpl_();
    virtual MethodTreeMgr* createMethodTreeMgr_(Heap*) = 0;
    virtual void procReset_();

    typedef DelegateEvent<void*> ResetEvent;

    bool mReserveReset;
    void* mResetParameter;
    ResetEvent mResetEvent;
    TaskMgr* mTaskMgr;
    MethodTreeMgr* mMethodTreeMgr;
    Heap* mMethodTreeMgrHeap;
};

} // namespace sead

#endif // SEAD_FRAMEWORK_H_
