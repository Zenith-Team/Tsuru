#pragma once

#include "tree.h"
#include "idisposer.h"
#include "bitflag.h"
#include "inamable.h"
#include "runtimetypeinfo.h"
#include "criticalsection.h"

namespace sead {

template <typename T, typename U>
class IDelegate2;

class MethodTreeNode : public TTreeNode<MethodTreeNode*>, INamable, IDisposer {
    SEAD_RTTI_BASE(MethodTreeNode)

public:
    enum PauseFlag {
        cPause_None = 0,
        cPause_Self = 1,
        cPause_Child = 2,
        cPause_Both = 3
    };

public:
    MethodTreeNode(CriticalSection* cs);

    virtual ~MethodTreeNode() {
        detachAll();
    }

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
