#pragma once

#include "types.h"

#define DECLARE_STATE(CLASS, NAME)                      \
    static State<CLASS> StateID_##NAME;                 \
    void beginState_##NAME();                           \
    void executeState_##NAME();                         \
    void endState_##NAME()

#define DECLARE_STATE_VIRTUAL(CLASS, NAME)              \
    static StateVirtual<CLASS> StateID_##NAME;          \
    virtual void beginState_##NAME();                   \
    virtual void executeState_##NAME();                 \
    virtual void endState_##NAME()

#define DECLARE_STATE_OVERRIDE(CLASS, NAME)             \
    static StateVirtual<CLASS> StateID_##NAME;          \
    void beginState_##NAME() override;                  \
    void executeState_##NAME() override;                \
    void endState_##NAME() override

#define CREATE_STATE(CLASS, NAME)                       \
    State<CLASS> CLASS::StateID_##NAME                  \
        (&CLASS::beginState_##NAME,                     \
         &CLASS::executeState_##NAME,                   \
         &CLASS::endState_##NAME)

#define CREATE_STATE_VIRTUAL(CLASS, NAME)               \
    StateVirtual<CLASS> CLASS::StateID_##NAME           \
        (&CLASS::beginState_##NAME,                     \
         &CLASS::executeState_##NAME,                   \
         &CLASS::endState_##NAME,                       \
         &StateBase::sNullState)

#define CREATE_STATE_OVERRIDE(CLASS, BASECLASS, NAME)   \
    StateVirtual<CLASS> CLASS::StateID_##NAME           \
        (&CLASS::beginState_##NAME,                     \
         &CLASS::executeState_##NAME,                   \
         &CLASS::endState_##NAME,                       \
         &BASECLASS::StateID_##NAME)


class StateBase {
public:
    inline StateBase() {
        this->mID = sCurrentID++;
    }

    virtual ~StateBase() { }

    virtual s32 getRootID() {
        return mID;
    }

    inline bool isEqual(StateBase* other) {
        return this->getRootID() == other->getRootID();
    }

    static StateBase sNullState;

    s32 mID;

private:
    static s32 sCurrentID;
};

template <class TOwner>
class State : public StateBase { //size: 0x20
public:
    typedef void (TOwner::*funcPtr)();

    State(funcPtr begin, funcPtr execute, funcPtr end)
        : mBegin(begin), mExecute(execute), mEnd(end)
    { }

protected:
    funcPtr mBegin;     // _8
    funcPtr mExecute;   // _10
    funcPtr mEnd;       // _18
};

template <class TOwner>
class StateVirtual : public State<TOwner> {
public:
    typedef void (TOwner::*funcPtr)();

    StateVirtual(funcPtr begin, funcPtr execute, funcPtr end, StateBase* baseState)
        : State<TOwner>(begin, execute, end), mBaseState(baseState)
    { }

    virtual ~StateVirtual() { }

    s32 getRootID() override {
        if (mBaseState->mID != -1)
            return mBaseState->getRootID();

        return mID;
    }

private:
    StateBase* mBaseState;
};

class StateMethodExecutorBase {
public:
    virtual ~StateMethodExecutorBase();
    virtual StateBase* getCurrentState() = 0;
    virtual void execute() = 0;
};

template <class TOwner>
class StateMethodExecutor : public StateMethodExecutorBase {
public:
    StateBase* getCurrentState() override;
    void execute() override;

    TOwner* mOwner;                 // _4
    State<TOwner>* mCurrentState;   // _8
};

class StateExecutorBase {
public:
    virtual StateMethodExecutorBase* begin(StateBase* nextState) = 0;
    virtual void end(StateMethodExecutorBase* methodExecutor) = 0;
    virtual StateMethodExecutorBase* setState(StateBase* state) = 0;
    virtual void resetState(StateMethodExecutorBase* methodExecutor) = 0;
    virtual StateMethodExecutorBase* callBegin(StateMethodExecutorBase* methodExecutor) = 0;
};

template <class TOwner>
class StateExecutor : public StateExecutorBase {
public:
    StateMethodExecutorBase* begin(StateBase* nextState) override;
    void end(StateMethodExecutorBase* methodExecutor) override;
    StateMethodExecutorBase* setState(StateBase* state) override;
    void resetState(StateMethodExecutorBase* methodExecutor) override;
    StateMethodExecutorBase* callBegin(StateMethodExecutorBase* methodExecutor) override;

    StateMethodExecutor<TOwner> mMethodExecutor;
};

class StateMgr {
public:
    StateMgr(StateExecutorBase* executor, StateBase* firstState = &StateBase::sNullState);

    StateBase* getCurrentState();
    void execute();
    void changeState(StateBase* pNextState);

    StateExecutorBase* mExecutor;
    StateBase* mNextState;
    StateMethodExecutorBase* mCurrentMethodExecutor;
    StateBase* mLastState;
};

template <class TOwner>
class StateWrapper {
public:
    virtual ~StateWrapper() { }

    StateExecutor<TOwner> mExecutor;
    StateMgr manager;

    inline void changeState(StateBase* nextState) {
        mManager.changeState(nextState);
    }

    inline void execute() {
        mManager.execute();
    }

    inline StateBase* currentState() {
        return mExecutor.mMethodExecutor.mCurrentState;
    }

    inline StateBase* lastState() {
        return mManager.mLastState;
    }
};

template <class TOwner>
class MultiStateWrapper {
public:
    virtual ~MultiStateWrapper() { }

    StateExecutor<TOwner> mExecutor;
    StateMgr mManager;
    StateBase* _20;

    inline void changeState(StateBase* nextState) {
        mManager.changeState(nextState);
    }

    inline void execute() {
        mManager.execute();
    }

    inline StateBase* currentState() {
        return mExecutor.mMethodExecutor.mCurrentState;
    }

    inline StateBase* lastState() {
        return mManager.mLastState;
    }
};
