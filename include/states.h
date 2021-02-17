#pragma once

#include "types.h"


#define DECLARE_STATE(CLASS, NAME)                      \
	static State<CLASS> StateID_##NAME;                 \
	void beginState_##NAME();                           \
	void executeState_##NAME();                         \
    void endState_##NAME();

#define DECLARE_STATE_VIRTUAL(CLASS, NAME)              \
	static StateVirtual<CLASS> StateID_##NAME;          \
	virtual void beginState_##NAME();                   \
	virtual void executeState_##NAME();                 \
    virtual void endState_##NAME();

#define DECLARE_STATE_OVERRIDE(CLASS, NAME)             \
	static StateVirtual<CLASS> StateID_##NAME;          \
	void beginState_##NAME() override;                  \
	void executeState_##NAME() override;                \
    void endState_##NAME() override;

#define CREATE_STATE(CLASS, NAME)                       \
    State<CLASS> CLASS::StateID_##NAME                  \
		(&CLASS::beginState_##NAME,                     \
         &CLASS::executeState_##NAME,                   \
         &CLASS::endState_##NAME);

#define CREATE_STATE_VIRTUAL(CLASS, NAME)               \
    StateVirtual<CLASS> CLASS::StateID_##NAME           \
		(&CLASS::beginState_##NAME,                     \
         &CLASS::executeState_##NAME,                   \
         &CLASS::endState_##NAME,                       \
         &StateBase::NullState);

#define CREATE_STATE_OVERRIDE(CLASS, BASECLASS, NAME)   \
    StateVirtual<CLASS> CLASS::StateID_##NAME           \
		(&CLASS::beginState_##NAME,                     \
         &CLASS::executeState_##NAME,                   \
         &CLASS::endState_##NAME,                       \
         &BASECLASS::StateID_##NAME);


class StateBase
{
public:
    inline StateBase()
    {
        this->id = currentId++;
    }

    virtual ~StateBase() { }
    virtual s32 getRootId()
    {
        return id;
    }

    inline bool isEqual(StateBase* other)
    {
        return this->getRootId() == other->getRootId();
    }

    static StateBase NullState;

    s32 id;

private:
    static s32 currentId;
};


template <class TOwner>
class State : public StateBase
{
public:
    typedef void (TOwner::*funcPtr)();

    State(funcPtr begin, funcPtr execute, funcPtr end)
        : begin(begin), execute(execute), end(end) { }

protected:
    funcPtr begin;
    funcPtr execute;
    funcPtr end;
};


template <class TOwner>
class StateVirtual : public State<TOwner>
{
public:
    typedef void (TOwner::*funcPtr)();

    StateVirtual(funcPtr begin, funcPtr execute, funcPtr end, StateBase* baseState)
        : State<TOwner>(begin, execute, end), baseState(baseState) { }
    virtual ~StateVirtual() { }

    s32 getRootId() override
    {
        if (baseState->id != -1)
            return baseState->getRootId();

        return id;
    }

private:
    StateBase* baseState;
};



class StateMethodExecuterBase
{
public:
    virtual ~StateMethodExecuterBase() { }
    virtual StateBase* getCurrentState() = 0;
    virtual void execute() = 0;
};

template <class TOwner>
class StateMethodExecuter : public StateMethodExecuterBase
{
public:
    StateBase* getCurrentState() override;
    void execute() override;

    TOwner* owner;
    State<TOwner>* currentState;
};


class StateExecuterBase
{
public:
    virtual StateMethodExecuterBase* begin(StateBase* nextState) = 0;
    virtual void end(StateMethodExecuterBase* methodExecuter) = 0;
    virtual StateMethodExecuterBase* setState(StateBase* state) = 0;
    virtual void resetState(StateMethodExecuterBase* methodExecuter) = 0;
    virtual StateMethodExecuterBase* callBegin(StateMethodExecuterBase* methodExecuter) = 0;
};

template <class TOwner>
class StateExecuter : public StateExecuterBase
{
public:
    StateMethodExecuterBase* begin(StateBase* nextState) override;
    void end(StateMethodExecuterBase* methodExecuter) override;
    StateMethodExecuterBase* setState(StateBase* state) override;
    void resetState(StateMethodExecuterBase* methodExecuter) override;
    StateMethodExecuterBase* callBegin(StateMethodExecuterBase* methodExecuter) override;

    StateMethodExecuter<TOwner> methodExecuter;     // 4
};


class StateMgr
{
public:
    StateMgr(StateExecuterBase* executer, StateBase* firstState = &StateBase::NullState);

    StateBase* getCurrentState();
    void execute();
    void changeState(StateBase* nextState);

    StateExecuterBase* executer;                    // 0
    StateBase* nextState;                           // 4
    StateMethodExecuterBase* currentMethodExecuter; // 8
    StateBase* lastState;                           // C
};


template <class TOwner>
class StateWrapper
{
public:
    virtual ~StateWrapper() { }

    StateExecuter<TOwner> executer;
    StateMgr manager;

    inline void changeState(StateBase* nextState) { manager.changeState(nextState); }
    inline void execute() { manager.execute(); }

    inline StateBase* currentState() { return executer.methodExecuter.currentState; }
    inline StateBase* lastState() { return manager.lastState; }
};
