#pragma once

#include "sead/tree.h"
#include "sead/idisposer.h"
#include "sead/bitflag.h"
#include "sead/inamable.h"
#include "sead/runtimetypeinfo.h"
#include "sead/criticalsection.h"

namespace sead {

template <typename T, typename U>
class IDelegate2;

class MethodTreeNode : public TTreeNode<MethodTreeNode*>, INamable, IDisposer {
    SEAD_RTTI_BASE(MethodTreeNode)

public:
    enum PauseFlag {
        None = 0,
        Self = 1,
        Child = 2,
        Both = 3
    };

public:
    MethodTreeNode(CriticalSection* cs);

    virtual ~MethodTreeNode();

    void attachMutexRec_(CriticalSection* m) const;
    void detachAll();
    void lock_();
    void unlock_();

    typedef IDelegate2<MethodTreeNode*, PauseFlag> PauseEventDelegate;

    struct { u32 data_[4]; } mDelegateHolder;
    mutable CriticalSection* mCriticalSection;
    u32 mPriority;
    BitFlag32 mPauseFlag;
    PauseEventDelegate* mPauseEventDelegate;
    void* mUserID;
};

}
