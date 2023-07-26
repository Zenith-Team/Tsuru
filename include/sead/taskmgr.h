#pragma once

#include "sead/task.h"

namespace sead {

class Framework;
class DelegateThread;
class NullFaderTask;

class TaskMgr
{
public:
    struct InitializeArg
    {
        InitializeArg(const TaskBase::CreateArg& rootTaskArg)
            : createQueueSize(0x20)
            , prepareStackSize(0x8000)
            , preparePriority(-1)
            , rootTaskCreateArg(rootTaskArg)
            , heap(nullptr)
            , parentFramework(nullptr)
        {
        }

        u32 createQueueSize;
        u32 prepareStackSize;
        s32 preparePriority;
        const TaskBase::CreateArg& rootTaskCreateArg;
        Heap* heap;
        Framework* parentFramework;
    };
    static_assert(sizeof(InitializeArg) == 0x18);

    class TaskCreateContextMgr;

public:
    TaskMgr(const InitializeArg& arg);

    static TaskMgr* initialize(const InitializeArg& arg);
    void finalize();

    void afterCalc();
    
    CriticalSection criticalSection;
    Framework* parentFramework;
    DelegateThread* prepareThread;
    NullFaderTask* nullFaderTask;
    TaskBase::List prepareList;
    TaskBase::List prepareDoneList;
    TaskBase::List activeList;
    TaskBase::List staticList;
    TaskBase::List dyingList;
    TaskBase::List destroyableList;
    HeapArray heapArray;
    TaskCreateContextMgr* taskCreateContextMgr;
    u32 maxCreateQueueSize;
    TaskBase* rootTask;
    TaskBase::CreateArg rootTaskCreateArg;
    TaskMgr::InitializeArg initializeArg;
    MethodTreeNode calcDestructionTreeNode;
    u32 _1A0;
    u32 _1A4;
};
static_assert(sizeof(TaskMgr) == 0x1A8);

}
