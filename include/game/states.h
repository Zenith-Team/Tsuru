#pragma once

#include <types.h>

class StateBase {
public:
    inline StateBase() {
        this->ID = sCurrentID++;
    }

    virtual ~StateBase() { }

    virtual s32 getRootID() {
        return ID;
    }

    inline bool isEqual(StateBase* other) {
        return this->getRootID() == other->getRootID();
    }

    static StateBase sNullState;

    s32 ID;

private:
    static s32 sCurrentID;
};

template <class TOwner>
class State : public StateBase { // Size: 0x20
    typedef void (TOwner::*PTMF)();

public:
    State(PTMF begin, PTMF execute, PTMF end)
        : begin(begin), execute(execute), end(end)
    { }

protected:
    PTMF begin;     // _8
    PTMF execute;   // _10
    PTMF end;       // _18
};

template <class TOwner>
class StateVirtual : public State<TOwner> {
    typedef void (TOwner::*PTMF)();

public:
    StateVirtual(PTMF begin, PTMF execute, PTMF end, StateBase* baseState)
        : State<TOwner>(begin, execute, end), baseState(baseState)
    { }

    virtual ~StateVirtual() { }

    s32 getRootID() override {
        if (baseState->ID != -1)
            return baseState->getRootID();

        return ID;
    }

private:
    StateBase* baseState;
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

    TOwner* owner;                 // _4
    State<TOwner>* currentState;   // _8
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

    StateMethodExecutor<TOwner> methodExecutor;
};

class StateMgr {
public:
    StateMgr(StateExecutorBase* executor, StateBase* firstState = &StateBase::sNullState);

    StateBase* getCurrentState();
    void execute();
    void changeState(StateBase* nextState);

    StateExecutorBase* executor;
    StateBase* nextState;
    StateMethodExecutorBase* currentMethodExecutor;
    StateBase* prevState;
};

template <class TOwner>
class StateWrapper {
public:
    virtual ~StateWrapper() { }

    StateExecutor<TOwner> executor;
    StateMgr manager;

    inline void changeState(StateBase* nextState) {
        manager.changeState(nextState);
    }

    inline void execute() {
        manager.execute();
    }

    inline StateBase* currentState() {
        return executor.methodExecutor.currentState;
    }

    inline StateBase* lastState() {
        return manager.prevState;
    }
};

template <class TOwner>
class MultiStateWrapper {
public:
    virtual ~MultiStateWrapper() { }

    StateExecutor<TOwner> executor;
    StateMgr manager;
    StateBase* _20;

    inline void changeState(StateBase* nextState) {
        manager.changeState(nextState);
    }

    inline void execute() {
        manager.execute();
    }

    inline StateBase* currentState() {
        return executor.methodExecutor.currentState;
    }

    inline StateBase* lastState() {
        return manager.prevState;
    }
};

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
