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
        Type_Invalid = 0,
        Type_Int     = 1,
        Type_Factory = 2,
        Type_String  = 3
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
        State_Created     = 0,
        State_Prepare     = 1,
        State_PrepareDone = 2,
        State_Sleep       = 3,
        State_Running     = 4,
        State_Dying       = 5,
        State_Destroyable = 6,
        State_Dead        = 7
    };

    enum Tag {
        Tag_System  = 0,
        Tag_App     = 1
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
    virtual MethodTreeNode* getMethodTreeNode(s32 methodType) = 0;
    virtual void onDestroy();                   // deleted

    void adjustHeapAll();

    TaskParameter* parameter;               // 2C
    BitFlag32 internalFlag;                 // 30
    TListNode<TaskBase*> taskListNode;      // 34
    HeapArray heapArray;                    // 44
    TaskMgr* taskMgr;                       // 5C
    State state;                            // 60
    Tag tag;                                // 64
    TaskClassID classID;                    // 68
};

static_assert(sizeof(TaskBase) == 0x74, "sead::TaskBase size mismatch");

class CalculateTask : public TaskBase { // Size: 0xC8
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

static_assert(sizeof(CalculateTask) == 0xC8, "sead::CalculateTask size mismatch");

}

#define SEAD_SINGLETON_TASK(CLASS)                                      \
public:                                                                 \
    static CLASS* instance() { return sInstance; }                      \
    static void setInstance(sead::TaskBase* task);                      \
                                                                        \
protected:                                                              \
    static CLASS* sInstance;                                            \
                                                                        \
private:                                                                \
    class TaskSingleton {                                               \
    public:                                                             \
        TaskSingleton() : set(false) { }                                \
        ~TaskSingleton() {                                              \
            if (set) CLASS::sInstance = nullptr;                        \
        }                                                               \
                                                                        \
        bool set;                                                       \
    };                                                                  \
                                                                        \
    friend class TaskSingleton;                                         \
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
