#pragma once

#include "sead/tree.h"
#include "sead/idisposer.h"
#include "sead/bitflag.h"
#include "sead/inamable.h"
#include "sead/runtimetypeinfo.h"
#include "sead/criticalsection.h"
#include "sead/delegate.h"
namespace sead {

class MethodTreeNode : public TTreeNode<MethodTreeNode*>, public INamable, public IDisposer {
    SEAD_RTTI_BASE(MethodTreeNode);

public:
    enum PauseFlag {
        Pause_None = 0,
        Pause_Self = 1,
        Pause_Child = 2,
        Pause_Both = 3
    };

public:
    MethodTreeNode(CriticalSection* cs);

    virtual ~MethodTreeNode();

    void attachMutexRec_(CriticalSection* m) const;
    void detachAll();
    void lock_();
    void unlock_();

    void setPauseFlag(PauseFlag flag)
    {
        this->lock_();

        if (pauseEventDelegate)
            pauseEventDelegate->invoke(this, flag);

        pauseFlag.setDirect(flag);

        this->unlock_();
    }

    typedef IDelegate2<MethodTreeNode*, PauseFlag> PauseEventDelegate;

    struct { u32 data_[4]; } delegateHolder;
    mutable CriticalSection* criticalSection;
    u32 priority;
    BitFlag32 pauseFlag;
    PauseEventDelegate* pauseEventDelegate;
    void* userID;
};

class MethodTreeMgr
{
    SEAD_RTTI_BASE(MethodTreeMgr);

public:
    MethodTreeMgr();
    virtual ~MethodTreeMgr();

    virtual void attachMethod(s32 methodType, MethodTreeNode* node) = 0;
    virtual MethodTreeNode* getRootMethodTreeNode(s32 methodType) = 0;
    virtual void pauseAll(bool p) = 0;
    virtual void pauseAppCalc(bool p) = 0;

    CriticalSection criticalSection;
};
static_assert(sizeof(MethodTreeMgr) == 0x40);

class DualScreenMethodTreeMgr : public MethodTreeMgr
{
    SEAD_RTTI_OVERRIDE(DualScreenMethodTreeMgr, MethodTreeMgr);

public:
    DualScreenMethodTreeMgr();
    ~DualScreenMethodTreeMgr() override;

    void attachMethod(s32 methodType, MethodTreeNode* node) override;
    MethodTreeNode* getRootMethodTreeNode(s32 methodType) override;
    void pauseAll(bool p) override;
    void pauseAppCalc(bool p) override;

    MethodTreeNode rootCalcNode;
    MethodTreeNode sysCalcNode;
    MethodTreeNode appCalcNode;
    MethodTreeNode topRootDrawNode;
    MethodTreeNode topSysDrawNode;
    MethodTreeNode topAppDrawNode;
    MethodTreeNode topAppDrawFinalNode;
    MethodTreeNode btmRootDrawNode;
    MethodTreeNode btmSysDrawNode;
    MethodTreeNode btmAppDrawNode;
    MethodTreeNode btmAppDrawFinalNode;
    u32 _3DC;
    u32 _3E0;
};
static_assert(sizeof(DualScreenMethodTreeMgr) == 0x3E4);

}
