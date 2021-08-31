#pragma once

#include <sead/list.h>
#include <sead/tree.h>
#include <sead/heappolicies.h>
#include <sead/idisposer.h>
#include <sead/bitflag.h>
#include <sead/inamable.h>
#include <sead/runtimetypeinfo.h>
#include <sead/methodtree.h>

namespace sead {

class TaskMgr;
class TaskBase;
class TaskEvent;
class TaskParameter;
class FaderTaskBase;

struct TaskConstructArg {
    HeapArray* heapArray;
    TaskMgr* mgr;
    TaskParameter* param;
};

typedef TaskBase* (*TaskFactory)(const TaskConstructArg&);

class TaskClassID {
public:
    enum Type {
        cInvalid = 0,
        cInt     = 1,
        cFactory = 2,
        cString  = 3
    };

public:
    Type type;
    union {
        s32 integer;
        TaskFactory factory;
        const char* string;
    } id;
};

class TaskUserID {
public:
    s32 id;
};

class TaskBase : public TTreeNode<TaskBase*>, public IDisposer, public INamable {
    SEAD_RTTI_BASE(TaskBase)

public:
    enum State {
        cCreated     = 0,
        cPrepare     = 1,
        cPrepareDone = 2,
        cSleep       = 3,
        cRunning     = 4,
        cDying       = 5,
        cDestroyable = 6,
        cDead        = 7
    };

    enum Tag {
        cSystem  = 0,
        cApp     = 1
    };

    struct CreateArg {
        typedef void (*SingletonFunc)(TaskBase*);

        TaskClassID factory;
        HeapPolicies heapPolicies;
        TaskBase* parent;
        TaskParameter* parameter;
        FaderTaskBase* fader;
        TaskBase* srcTask;
        TaskBase** createdTask;
        void* createCallback;  // DelegateEvent<TaskBase*>::Slot*
        TaskUserID userID;
        Tag tag;
        SingletonFunc instanceCB;
    };

public:
    TaskBase(const TaskConstructArg& arg, const char* name);

    virtual void pauseCalc(bool b) = 0;
    virtual void pauseDraw(bool b) = 0;
    virtual void pauseCalcRec(bool b) = 0;
    virtual void pauseDrawRec(bool b) = 0;
    virtual void pauseCalcChild(bool b);        // deleted
    virtual void pauseDrawChild(bool b);        // deleted
    virtual ~TaskBase();
    virtual void prepare();
    virtual void enterCommon();
    virtual void enter();
    virtual void exit();
    virtual void onEvent(const TaskEvent&);
    virtual void attachCalcImpl() = 0;
    virtual void attachDrawImpl() = 0;
    virtual void detachCalcImpl() = 0;
    virtual void detachDrawImpl() = 0;
    virtual const RuntimeTypeInfo::Interface* getCorrespondingMethodTreeMgrTypeInfo() const = 0;
    virtual MethodTreeNode* getMethodTreeNode(s32 method_type) = 0;
    virtual void onDestroy();                   // deleted

    TaskParameter* parameter;  // _2C
    BitFlag32 internalFlag;    // _30
    ListNode taskListNode;     // _34
    HeapArray heapArray;       // _44
    TaskMgr* taskMgr;          // _5C
    State state;               // _60
    Tag tag;                   // _64
    TaskClassID classID;       // _68
};

class CalculateTask : public TaskBase {
    SEAD_RTTI_OVERRIDE(CalculateTask, TaskBase)

public:
    CalculateTask(const TaskConstructArg& arg, const char* name);
    virtual ~CalculateTask();

    void pauseCalc(bool b) override;
    void pauseDraw(bool b) override;
    void pauseCalcRec(bool b) override;     // deleted
    void pauseDrawRec(bool b) override;     // deleted

    void attachCalcImpl() override;
    void attachDrawImpl() override;
   void detachCalcImpl() override;
   void detachDrawImpl() override;

    const RuntimeTypeInfo::Interface* getCorrespondingMethodTreeMgrTypeInfo() const override;   // deleted
    MethodTreeNode* getMethodTreeNode(s32 methodType) override;

    virtual void calc();
    
    MethodTreeNode calcNode;
};

}

#define SEAD_SINGLETON_TASK(CLASS)                                      \
public:                                                                 \
    class TaskSingleton {                                               \
    public:                                                             \
        TaskSingleton() : set(false) { }                                \
        ~TaskSingleton() {                                              \
            if (set)                                                    \
                CLASS::sInstance = nullptr;                             \
        }                                                               \
                                                                        \
        bool set;                                                       \
    };                                                                  \
                                                                        \
    static void setInstance(sead::TaskBase* task);                      \
    static CLASS* sInstance;                                            \
                                                                        \
    TaskSingleton taskSingleton;

#define SEAD_SET_SINGLETON_TASK(CLASS)                                  \
    void CLASS::setInstance(sead::TaskBase* task) {                     \
        if (CLASS::sInstance)                                           \
            return;                                                     \
        CLASS::sInstance = reinterpret_cast<CLASS*>(task);              \
        reinterpret_cast<CLASS*>(task)->taskSingleton.set = true;       \
    }

#define SEAD_SINGLETON_TASK_IMPL(CLASS)                                 \
    SEAD_SET_SINGLETON_TASK(CLASS)                                      \
    CLASS* CLASS::sInstance = nullptr;
