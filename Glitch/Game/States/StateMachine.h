#pragma once
#include "IState.h"
#include "IGlobalState.h"

/// @brief 
/// Statemachine
/// T for entity
template <typename T>
class StateMachine
{
private:
    IState<T>* currentState;
    IGlobalState<T>* globalState;
public:
    ~StateMachine() {
        delete currentState;
        delete globalState;
    }

    /// @brief 
    /// set current state
    void setCurrentState(IState<T>* _state, T* entity) {
        this->currentState = _state;
        this->currentState->entry(entity);
    };

    /// @brief 
    /// get current state
    IState<T>& getCurrentState() const { return *this->currentState; };

    /// @brief 
    /// set global state
    void setGlobalState(IGlobalState<T>* _globalState) {
        this->globalState = _globalState;
    };

    /// @brief 
    /// update current and global state
    void update(T* entity) {
        this->currentState->execute(entity);
        this->globalState->execute(entity);
    };

    /// @brief 
    /// change state
    void changeState(IState<T>* _state, T* entity) {
        if (currentState != _state && _state) return;

        currentState->exit(entity);
        delete currentState;
        currentState = _state;
        currentState->entry(entity);
    };
};