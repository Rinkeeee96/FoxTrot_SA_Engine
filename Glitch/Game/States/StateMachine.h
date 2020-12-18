#pragma once
#include "IState.h"

/// @brief 
/// Statemachine
/// T for entity
template <typename T>
class StateMachine
{
private:
    unique_ptr<IState<T>> currentState;
    unique_ptr<IState<T>> globalState;
public:
    ~StateMachine() { }

    /// @brief 
    /// set current state
    void setCurrentState(unique_ptr<IState<T>> _state, T& entity) {
        this->currentState = move(_state);
        this->currentState->entry(entity);
    };

    /// @brief 
    /// get current state
    IState<T>& getCurrentState() const { return *this->currentState; };
    IState<T>& getGlobalState() const { return *this->globalState; };

    /// @brief 
    /// set global state
    void setGlobalState(unique_ptr<IState<T>> _globalState, T& entity) {
        this->globalState = move(_globalState);
        this->globalState->entry(entity);
    };

    /// @brief 
    /// update current and global state
    void update(T& entity) {
        this->currentState->execute(entity);
        this->globalState->execute(entity);
    };

    /// @brief 
    /// change state
    void changeState(unique_ptr<IState<T>> _state, T& entity) {
        if (currentState != _state && _state)
        {
            currentState->exit(entity);
            currentState = move(_state);
            currentState->entry(entity);
        }
    };
};